#pragma once

#include "sfwdraw.h"
#include "BaseState.h"
#include "Factory.h"


/*
	The gamestate represents a discrete container of all that is 
	necessary to drive the game experience.

	A factory object is used to manage the creation and deletion of
	objects in the simulation.

	The game state updates the entities within the factory using
	a series of 'systems.'
*/

class GameState : public BaseState
{
	Factory factory;
	unsigned spr_space, spr_ball, spr_paddle, spr_font, spr_wall;
	ObjectPool<Entity>::iterator obj_paddle;
	ObjectPool<Entity>::iterator obj_ball;
	ObjectPool<Entity>::iterator currentCamera;
	ObjectPool<Entity>::iterator TopWall;
	ObjectPool<Entity>::iterator BottomWall;
	ObjectPool<Entity>::iterator LeftWall;
	ObjectPool<Entity>::iterator RightWall;

public:
	virtual void init()
	{
		spr_paddle = sfw::loadTextureMap("../res/Paddle.png");
		spr_ball = sfw::loadTextureMap("../res/ball.png");
		spr_font = sfw::loadTextureMap("../res/font.png",32,4);
		spr_space = sfw::loadTextureMap("../res/space.jpg");
		spr_wall = sfw::loadTextureMap("../res/bullet.png");
	}

	virtual void play()
	{
		// delete any old entities sitting around
		for (auto it = factory.begin(); it != factory.end(); it->onFree(), it.free());

		// setup a default camera
		currentCamera = factory.spawnCamera(800, 600, 1);
		currentCamera->transform->setGlobalPosition(vec2{ 400, 300 });

		// call some spawning functions!
		factory.spawnStaticImage(spr_space, 0, 0, 800, 600);
		obj_paddle = factory.spawnPlayer(spr_paddle, spr_font);
		obj_ball = factory.spawnBall(spr_ball, vec2{25, 400}, 1.f);
		obj_paddle->transform->setGlobalPosition({ 200,200 });
		obj_ball->transform->setGlobalPosition({ 100,100 });
		TopWall = factory.spawnWall(spr_wall, { 0, 350 }, { 800, 100 });
		BottomWall = factory.spawnWall(spr_wall, { 0, -350 }, { 800, 100 });
		LeftWall = factory.spawnWall(spr_wall, { -450, 0 }, { 100, 600 });
		RightWall = factory.spawnWall(spr_wall, { 450, 0 }, { 100, 600 });
	}

	virtual void stop()
	{

	}

	// should return what state we're going to.
	// REMEMBER TO HAVE ENTRY AND STAY states for each application state!
	virtual size_t next() const { return 0; }


	// update loop, where 'systems' exist
	virtual void step()
	{
		float dt = sfw::getDeltaTime();

		// maybe spawn some asteroids here.

		for(auto it = factory.begin(); it != factory.end();) // no++!
		{
			bool del = false; // does this entity end up dying?
			auto &e = *it;    // convenience reference

			// rigidbody update
			if (e.transform && e.rigidbody)
				e.rigidbody->integrate(&e.transform, dt);

			// controller update
			if (e.transform && e.controller)
			{
				e.controller->poll(&e.transform, &e.rigidbody, dt);
			}
			// lifetime decay update
			if (e.lifetime)
			{
				e.lifetime->age(dt);
				if (!e.lifetime->isAlive())
					del = true;
			}

			if (e.wall)
				e.wall->step(&e.transform, &e.rigidbody);

			if (e.ball)
				e.ball->step(&e.transform, &e.rigidbody);

			// ++ here, because free increments in case of deletions
			if (!del) it++;
			else
			{
				it->onFree();
				it.free();
			}
		}


		// Physics system!
		// You'll want to extend this with custom collision responses

		
		for(auto it = factory.begin(); it != factory.end(); it++) // for each entity
			for(auto bit = it; bit != factory.end(); bit++)		  // for every other entity
				if (it != bit && it->transform && it->collider && bit->transform && bit->collider)
				// if they aren't the same and they both have collidable bits...
				{
					// test their bounding boxes
					if (base::BoundsTest(&it->transform, &it->collider, &bit->transform, &bit->collider))
					{
						// if true, get the penetration and normal from the convex hulls
						auto cd = base::ColliderTest(&it->transform, &it->collider, &bit->transform, &bit->collider);
						
						// if there was a collision,
						if (cd.result())
						{
							// condition for dynamic resolution
							if (it->rigidbody && bit->rigidbody)
								base::DynamicResolution(cd,&it->transform,&it->rigidbody, &bit->transform, &bit->rigidbody);
							
							// condition for static resolution
							else if (it->rigidbody && !bit->rigidbody)							
								base::StaticResolution(cd, &it->transform, &it->rigidbody);					
						}
					}
				}

	}


	virtual void draw()	
	{
		// kind of round about, but this is the camera matrix from the factory's current camera
		auto cam = currentCamera->camera->getCameraMatrix(&currentCamera->transform);

		// draw sprites
		for each(auto &e in factory)
			if (e.transform && e.sprite)
				e.sprite->draw(&e.transform, cam);

		// draw text
		for each(auto &e in factory)
			if (e.transform && e.text)
				e.text->draw(&e.transform, cam);


#ifdef _DEBUG
		for each(auto &e in factory)
			if (e.transform)
				e.transform->draw(cam);

		for each(auto &e in factory)
			if (e.transform && e.collider)
				e.collider->draw(&e.transform, cam);

		for each(auto &e in factory)
			if (e.transform && e.rigidbody)
				e.rigidbody->draw(&e.transform, cam);
#endif
	}
};
