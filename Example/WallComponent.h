#pragma once

#include "Base.h"
using namespace base;

class Wall
{

public:
	
	vec2 pos;
	vec2 scale;

	void step(base::Transform *T, base::Rigidbody *rb)
	{
		T->setGlobalPosition(pos);
		T->setGlobalScale(scale);
		rb->acceleration = { 0,0 };
		rb->angularAcceleration = 0;
		rb->velocity = { 0,0 };
		rb->angularVelocity = 0;
	}

};