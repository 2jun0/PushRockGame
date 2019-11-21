#pragma once
#include "ent.h"
// entities
#include "wall.h"
#include "rock.h"
#include "player.h"
#include "button.h"

class EntFactory {
protected:
	Ent* ent;
public:
	void createEntity(const EntType& type, const Pos& pos);
	Ent* getEntity();
};