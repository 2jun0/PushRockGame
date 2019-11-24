#include "wall.h"

const Aabb Wall::WALL_AABB = Aabb(-0.5, 0.5, -0.5, 0.5);

Wall::Wall(const Pos& pos): Ent(WALL_AABB, pos, EntType::WALL){

}

void Wall::draw() {
	glPushMatrix();
	{
		glColor3f(0.47, 0.3, 0.22);
		glTranslatef(0.0, 0.5, 0.0); 
		glutWireCube(1.0);
	}
	glPopMatrix();
}