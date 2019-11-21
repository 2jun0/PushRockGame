#include "ent_factory.h"

void EntFactory::createEntity(const EntType& type, const Pos& pos) {
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

Ent* EntFactory::getEntity() {
	return ent;
}