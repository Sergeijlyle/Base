#pragma once

#include "Base.h"
using namespace base;

class PlayerController
{

public:
	float speed = 5, turnSpeed = 0;

	float shotTimer = 0.0f;
	bool shotRequest = false;

	void poll(base::Transform *T, base::Rigidbody *rb, float dt)
	{
		vec2 stuff = vec2{ T->getGlobalPosition().x, sfw::getMouseY() };
		T->setLocalPosition(stuff);
	}

};