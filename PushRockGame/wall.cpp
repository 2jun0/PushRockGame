#include "wall.h"

const Aabb Wall::WALL_AABB = Aabb(-0.5, 0.5, -0.5, 0.5);

Wall::Wall(const Pos& pos): Ent(WALL_AABB, pos, EntType::WALL){

}

void Wall::draw() {
	glPushMatrix();
	{
		
	}
	glPopMatrix();
}