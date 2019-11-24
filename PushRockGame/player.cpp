#include "player.h"

const Aabb Player::PLAYER_AABB = Aabb(-0.5, 0.5, -0.5, 0.5);

Player::Player(const Pos& pos) : Ent(PLAYER_AABB, pos, EntType::PLAYER) {

}

void Player::draw() {
	glPushMatrix();
	glTranslatef(0.0, 0.4, 0.0);
	glColor3f(1, 0, 0);
	glScalef(0.4, 0.4, 0.4);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.45, 0.3, 0.0);
	glColor3f(1, 0.5, 0.2);
	glScalef(0.1, 0.3, 0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.45, 0.3, 0.0);
	glColor3f(1, 0.5, 0.2);
	glScalef(0.1, 0.3, 0.1);
	glPopMatrix();

}