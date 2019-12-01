#pragma once
#include "ent.h"

class Wall : public Ent {
public:
	static const Aabb WALL_AABB;
	static const float COLOR[];
public:
	Wall(const Pos& pos);

	virtual void draw();
	virtual const float* getColor();
};