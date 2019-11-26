#include "button.h"
const GLfloat Pi = 3.1415926536f;
const Aabb Button::BUTTON_AABB = Aabb(-0.5, 0.5, -0.5, 0.5);

Button::Button(const Pos& pos) : Ent(BUTTON_AABB, pos, EntType::BUTTON) {

}

void Button::draw() {
	glPushMatrix();
	{
		glBegin(GL_LINE_STRIP);
		GLint n = 3600;
		for (GLint i = 0; i < n; i++) {
			glVertex2f(circ.x + radius * cos(twoPi * i / n), circ.y + radius * sin(twoPi * i / n));
		}
		glEnd();

	glPopMatrix();
}