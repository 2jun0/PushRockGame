#include "ent_builder.h"

void EntBuilder::createEntity(EntType& type, Pos& pos) {
	switch (type)
	{
	case EntType::WALL:
		ent = new Wall(pos);
		break;
	case EntType::ROCK:
		ent = new Rock(pos);
		break;
	case EntType::PLAYER:
		ent = new Player(pos);
		break;
	case EntType::BUTTON:
		ent = new Button(pos);
		break;
	default:
		break;
	}
}

Ent* EntBuilder::getEntity() {
	return ent;
}