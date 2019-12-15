#include "game.h"
#include "button.h"
#include "sound_manager.h"

const Aabb Button::BUTTON_AABB = Aabb(-0.5, 0.5, -0.5, 0.5);
const float Button::PRESSED_COLOR[] = {1.0, 1.0, 0.0};
const float Button::UNPRESSED_COLOR[] = {0.8, 0.8, 0.0};

Button::Button(const Pos& pos) : Ent(BUTTON_AABB, pos, EntType::BUTTON) {
	isPressed = false;
}

bool Button::getIsPressed() {
	return isPressed;
}

void Button::draw() {
	// 충돌된 돌이 있으면 true로 설정
	isPressed = (Game::getInstance().getCollisionEntity(this, EntType::ROCK)) ? true : false;

	glPushMatrix();
	{
		if (isPressed) {
			//glColor3f(1.0, 1.0, 0.0); 
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PRESSED_COLOR);// 눌렸을 때, 색깔
		}
		else {
			//glColor3f(0.8, 0.8, 0.0);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, UNPRESSED_COLOR);// 안 눌렸을 때, 색깔
		}
		glScalef(1, 0, 1);
		glutSolidCube(1);
	}
	glPopMatrix();
}

bool Button::collisionEvent(Ent& ent)  {

	return false;
}

void Button::afterCollisionEvent(Ent& ent, bool isCollision) {
	if ((!isCollision && ent.getType() == EntType::ROCK) && !isPressed) {
		SoundManager::getInstance().play(SoundRes::BUTTON_PRESS_WAV);
	}
}

const float* Button::getColor() {
	if (isPressed) {
		return PRESSED_COLOR;
	}
	else {
		return UNPRESSED_COLOR;
	}
}