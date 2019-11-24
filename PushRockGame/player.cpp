#include "player.h"

const Aabb Player::PLAYER_AABB = Aabb(-0.5, 0.5, -0.5, 0.5);

Player::Player(const Pos& pos) : Ent(PLAYER_AABB, pos, EntType::PLAYER) {
	angles[PLAYER_ANGLE] = 0;
	angles[LEFT_ARM] = 90;
	angles[RIGHT_ARM] = 0;
}

void Player::draw() {
	glPushMatrix();
	{
		glTranslatef(0.0, 0.4, 0.0); // ���� ��ġ
		glRotatef(-angles[PLAYER_ANGLE], 0, 1, 0);
		// ���� �׸���
		glPushMatrix();
		{
			glColor3f(1, 0, 0);
			glScalef(0.5, 0.8, 0.4);
			glutWireCube(1);
		}
		glPopMatrix();

		// arms
		glPushMatrix();
		{
			glTranslatef(0, 0.15, 0); // ��� ��ġ
		
			// left arm
			glPushMatrix();
			{
				glTranslatef(-0.35, 0, 0); // ���� ��� ��ġ
				glRotatef(-angles[LEFT_ARM], 1, 0, 0); // �� ������
				glTranslatef(0, -0.15, 0); // ���� �� ��ġ
				drawArm(); // �� �׸���
			}
			glPopMatrix();

			// right arm
			glPushMatrix();
			{
				glTranslatef(0.35, 0, 0); // ������ ��� ��ġ
				glRotatef(-angles[RIGHT_ARM], 1, 0, 0); // �� ������
				glTranslatef(0, -0.15, 0); // ������ �� ��ġ
				drawArm(); // �� �׸���
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void Player::drawArm() {
	glPushMatrix();
	{
		glColor3f(0, 0, 1);
		glScalef(0.2, 0.5, 0.2);
		glutWireCube(1);
	}
	glPopMatrix();
}

void Player::rotate(float angle) {
	angles[PLAYER_ANGLE] = angle;
}