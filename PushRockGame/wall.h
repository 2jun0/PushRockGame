#pragma once
#include "ent.h"

class Wall : public Ent {
public:
	static const Aabb WALL_AABB;
public:
	Wall(Pos& pos);

	virtual void draw();
};