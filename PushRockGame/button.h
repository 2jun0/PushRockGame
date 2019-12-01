#pragma once
#include "ent.h"

class Button : public Ent {
public:
	static const Aabb BUTTON_AABB;
	static const float PRESSED_COLOR[];
	static const float UNPRESSED_COLOR[];
private:
	bool isPressed;
public:
	Button(const Pos& pos);

	bool getIsPressed();

	virtual bool collisionEvent(Ent& ent);
	virtual void afterCollisionEvent(Ent& ent, bool isCollision);

	virtual void draw();
	virtual const float* getColor();
};