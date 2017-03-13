#pragma once

#include "Entity.h"

class Factory
{	
	ObjectPool<Entity>	  entities;
	
	// The factory will store an object pool for each component type
	ObjectPool<Transform> transforms;
	ObjectPool<Rigidbody> rigidbodies;
	ObjectPool<Collider>  colliders;
	ObjectPool<Sprite>    sprites;
	ObjectPool<Lifetime>  lifetimes;
	ObjectPool<Camera>    cameras;
	ObjectPool<Text>	  texts;
	ObjectPool<Wall>	  walls;
	ObjectPool<Ball>	  balls;
	ObjectPool<PlayerController> controllers;

public:

	// iterators to access the entity pool
	ObjectPool<Entity>::iterator begin() { return entities.begin(); }
	ObjectPool<Entity>::iterator end() { return entities.end(); }

	// for now, they're all the same size
	Factory(size_t size = 512)
								: entities(size), transforms(size), rigidbodies(size),
								  colliders(size), sprites(size), lifetimes(size),
								  cameras(size), controllers(size), texts(size), walls(size),
								  balls(size)
	{
	}

	// What follows are specialized spawning functions
	// just observe the steps taken and replicate for your own usages

	ObjectPool<Entity>::iterator spawnCamera(float w2, float h2, float zoom)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->camera = cameras.push();
		e->camera->offset = vec2{w2,h2};
		e->camera->scale = vec2{ zoom,zoom };
		return e;
	}

	ObjectPool<Entity>::iterator spawnStaticImage(unsigned sprite, float x, float y, float w, float h)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->sprite = sprites.push();
		e->sprite->sprite_id = sprite;
		e->sprite->dimensions = vec2{w,h};
		e->transform->setLocalPosition(vec2{ x,y });	
		return e;
	}


	ObjectPool<Entity>::iterator spawnPlayer(unsigned sprite, unsigned font)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		e->controller = controllers.push();
		e->text = texts.push();
		
		e->text->sprite_id = font;
		e->text->offset = vec2{ -24,-24 };
		e->text->off_scale = vec2{.5f,.5f};
		

		e->rigidbody->mass = 0.1f;
		e->rigidbody->drag = 50;

		e->transform->setLocalScale(vec2{18,96});

		e->sprite->sprite_id = sprite;
		//e->sprite->dimensions = vec2(1, 2);

		return e;
	}
	
	ObjectPool<Entity>::iterator spawnBall(unsigned sprite, vec2 pos, float impulse)
	{
		auto e = entities.push();
		e->ball = balls.push();
		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		e->transform->setLocalScale(vec2{ 48,48 });
		e->rigidbody->addImpulse(vec2{ 200,0 });
		e->sprite->sprite_id = sprite;

		return e;
	}

	ObjectPool<Entity>::iterator spawnPaddle(unsigned sprite, vec2 pos, float impulse)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		e->sprite->sprite_id = sprite;

		return e;
	}
	
	ObjectPool<Entity>::iterator spawnWall(unsigned sprite, vec2 pos, vec2 scl)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		e->wall = walls.push();
		e->sprite->sprite_id = sprite;
		e->transform->setGlobalPosition(pos);
		e->transform->setGlobalScale(scl);
		e->rigidbody->drag = 1000;
		e->rigidbody->mass = 1000;

		e->wall->pos = pos;
		e->wall->scale = scl;

		return e;
	}
	
};





