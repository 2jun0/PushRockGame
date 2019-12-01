#pragma once
#include "ent.h"

class Rock : public Ent {
public:
	static const Aabb ROCK_AABB;
	static const float COLOR[];
public:
	Rock(const Pos& pos);

	virtual void draw();

	virtual bool collisionEvent(Ent& ent);
	virtual const float* getColor();
};