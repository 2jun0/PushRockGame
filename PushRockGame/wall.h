#pragma once
#include "ent.h"

class Wall : public Ent {
public:
	static const Aabb WALL_AABB;
public:
	Wall(const Pos& pos);

	virtual void draw();
};