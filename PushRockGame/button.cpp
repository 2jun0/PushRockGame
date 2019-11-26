#include "game.h"
#include "button.h"

const Aabb Button::BUTTON_AABB = Aabb(-0.5, 0.5, -0.5, 0.5);

Button::Button(const Pos& pos) : Ent(BUTTON_AABB, pos, EntType::BUTTON) {
	isPressed = false;
}

void Button::draw() {
	// �浹�� ���� ������ true�� ����
	isPressed = (Game::getInstance().getCollisionEntity(this, EntType::ROCK)) ? true : false;

	glPushMatrix();
	{
		if (isPressed) {
			glColor3f(1.0, 1.0, 0.0); // ������ ��, ����
		}
		else {
			glColor3f(0.8, 0.8, 0.0); // �� ������ ��, ����
		}
		glBegin(GL_POLYGON);
		glVertex3f(-0.5, 0,-0.5);
		glVertex3f(0.5,0,-0.5);
		glVertex3f(0.5, 0, 0.5);
		glVertex3f(-0.5, 0, 0.5);
		glEnd();
	}
	glPopMatrix();
}

bool Button::collisionEvent(Ent& ent)  {
	return false;
}