#pragma once
#include "ent.h"

class Player : public Ent {
public:
	static const Aabb PLAYER_AABB;
public:
	Player(const Pos& pos);

	virtual void draw();
};