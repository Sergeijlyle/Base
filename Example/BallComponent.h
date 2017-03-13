#pragma once
#include "Base.h"
using namespace base;

class Ball
{
public:
	float minSpeed = 50;
	float randSpeed = 150;

	float RandRange(float min, float max)
	{
		return min + (rand() % (int)(max - min + 1));
	}

	void step(base::Transform *T, base::Rigidbody *rb)
	{
		if (rb->velocity.x < minSpeed && rb->velocity.x > -minSpeed &&
			rb->velocity.y < minSpeed && rb->velocity.y > -minSpeed)
		{
			T->setGlobalPosition({ 0,0 });
			rb->addImpulse({ RandRange(-randSpeed, randSpeed), 
							 RandRange(-randSpeed, randSpeed) });
		}
	}

};