#include "wall.h"

const Aabb Wall::WALL_AABB = Aabb(-0.5, 0.5, -0.5, 0.5);
const float Wall::COLOR[] = {0.47, 0.3, 0.22};

Wall::Wall(const Pos& pos): Ent(WALL_AABB, pos, EntType::WALL){

}

void Wall::draw() {
	glPushMatrix();
	{
		//glColor3f(0.47, 0.3, 0.22);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, COLOR);
		glTranslatef(0.0, 0.5, 0.0); 
		glutSolidCube(1.0);
	}
	glPopMatrix();
}

const float* Wall::getColor() {
	return COLOR;
}