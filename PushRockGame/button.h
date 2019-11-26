#pragma once
#include "ent.h"

class Button : public Ent {
public:
	static const Aabb BUTTON_AABB;
private:
	bool isPressed;
public:
	Button(const Pos& pos);

	virtual bool collisionEvent(Ent& ent);

	virtual void draw();
};