#pragma once
#include "ent.h"

class Button : public Ent {
public:
	static const Aabb BUTTON_AABB;
public:
	Button(const Pos& pos);

	virtual void draw();
};