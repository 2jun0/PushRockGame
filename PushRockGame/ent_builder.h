#pragma once
#include "ent.h"
// entities
#include "wall.h"
#include "rock.h"
#include "player.h"
#include "button.h"

class EntBuilder {
protected:
	Ent* ent;
public:
	void createEntity(EntType& type, Pos& pos);
	Ent* getEntity();
};