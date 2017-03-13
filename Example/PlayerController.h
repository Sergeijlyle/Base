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
		rb->addForce(vec2{ 0, sfw::getKey(KEY_UP) ? 1600.f : 0.f });
		rb->addForce(vec2{ 0, sfw::getKey(KEY_DOWN) ? -1600.f : 0.f });
		T->setGlobalPosition({ 200, T->getGlobalPosition().y });
	}

};