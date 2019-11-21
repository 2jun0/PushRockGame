#include "wall.h"

const Aabb Wall::WALL_AABB = Aabb(-0.5, 0.5, -0.5, 0.5);

Wall::Wall(const Pos& pos): Ent(WALL_AABB, pos, EntType::WALL){

}

void Wall::draw() {
	glPushMatrix();
	{
		glTranslatef(0.0, 0.5, 0.0); 
		glutSolidCube(1.0);
	}
	glPopMatrix();
}