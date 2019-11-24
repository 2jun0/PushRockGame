#pragma once
#include "ent.h"

class Player : public Ent {
public:
	static const Aabb PLAYER_AABB;
	static const int PLAYER_ANGLE = 0;
	static const int LEFT_ARM = 1;
	static const int RIGHT_ARM = 2;
	float angles[2];
public:
	Player(const Pos& pos);

	void rotate(float angle);
	virtual void draw();
private:
	void drawArm();
};