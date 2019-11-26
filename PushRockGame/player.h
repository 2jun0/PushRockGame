#pragma once
#include "ent.h"

class Player : public Ent {
public:
	static const Aabb PLAYER_AABB;
	static const int PLAYER_ANGLE = 0;
	static const int LEFT_ARM = 1;
	static const int RIGHT_ARM = 2;
private:
	float angles[3];
	bool isRaising;
	bool isRaised;
public:
	Player(const Pos& pos);

	float getPlayerAngle();
	bool getIsRaising();

	void rotate(float angle);
	virtual void draw();

	virtual bool moveLeft();
	virtual bool moveRight();
	virtual bool moveUp();
	virtual bool moveDown();
	void raiseArms();
	void unraiseArms();

	virtual bool collisionEvent(Ent& ent);
	virtual bool checkCollision(Ent& ent);

private:
	void drawArm();
};

void raiseArmsCall(int p);
void unraiseArmTimerCall(int p);
void unraiseArmsCall(int p);