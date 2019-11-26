#pragma once
#include "ent.h"

class Rock : public Ent {
public:
	static const Aabb ROCK_AABB;
public:
	Rock(const Pos& pos);

	virtual void draw();

	virtual void collisionEvent(Ent& ent);
};