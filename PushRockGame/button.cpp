#include "button.h"

const Aabb Button::BUTTON_AABB = Aabb(-0.5, 0.5, -0.5, 0.5);

Button::Button(const Pos& pos) : Ent(BUTTON_AABB, pos, EntType::BUTTON) {

}

void Button::draw() {
	glPushMatrix();
	{
		glColor3f(0.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex3f(-0.5, 0.0,-0.5);
		glVertex3f(0.5,0.0,-0.5);
		glVertex3f(0.5, 0.0, 0.5);
		glVertex3f(-0.5, 0.0, 0.5);
		glEnd();
	}
	glPopMatrix();
}