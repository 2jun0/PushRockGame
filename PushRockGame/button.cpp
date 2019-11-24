#include "button.h"

const Aabb Button::BUTTON_AABB = Aabb(-0.5, 0.5, -0.5, 0.5);

Button::Button(const Pos& pos) : Ent(BUTTON_AABB, pos, EntType::BUTTON) {

}

void Button::draw() {
	glPushMatrix();
	{
		float vctPnt[][3] = {
		{-0.5f,  -0.5f, 0.0f},
		{-0.5f,  0.5f, 0.0f},
		{ 0.5f, -0.5f, 0.0f},
		{0.5f, 0.5f, 0.0f}
		};

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 4; i++)
		{
			glVertex3f(vctPnt[i][0], vctPnt[i][1], vctPnt[i][2]);
		}
		glEnd();
	}
	glPopMatrix();
}