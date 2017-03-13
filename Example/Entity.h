#pragma once

#include "Base.h"

#include "PlayerController.h"
#include"WallComponent.h"
#include"BallComponent.h"

using namespace base;


class Entity
{
public:
	ObjectPool<Transform>::iterator transform;
	ObjectPool<Rigidbody>::iterator rigidbody;
	ObjectPool<Collider>::iterator  collider;
	ObjectPool<Lifetime>::iterator lifetime;
	ObjectPool<Sprite>::iterator sprite;
	ObjectPool<Camera>::iterator camera;
	ObjectPool<Text>::iterator text;

	// example of a component in this project
	ObjectPool<PlayerController>::iterator controller;
	ObjectPool<Wall>::iterator wall;
	ObjectPool<Ball>::iterator ball;

	void onFree()
	{
		transform.free();
		rigidbody.free();
		collider.free();
		lifetime.free();
		sprite.free();
		camera.free();
		text.free();

		controller.free();
		wall.free();
		ball.free();
	}
};