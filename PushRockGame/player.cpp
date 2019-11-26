#include <cmath>
#include "player.h"

const Aabb Player::PLAYER_AABB = Aabb(-0.4, 0.4, -0.4, 0.4);

Player::Player(const Pos& pos) : Ent(PLAYER_AABB, pos, EntType::PLAYER) {
	speed = 1;

	angles[PLAYER_ANGLE] = 0;
	angles[LEFT_ARM] = 0;
	angles[RIGHT_ARM] = 0;

	isRaising = false;
	isRaised = false;
}

// ------------------- draw ------------------//
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

float Player::getPlayerAngle() {
	return angles[PLAYER_ANGLE];
}
bool Player::getIsRaising(){
	return isRaising;
}

// --------------- collision -----------------//
void Player::collisionEvent(Ent& ent) {
	if (ent.getType() == EntType::ROCK) {
		if (!isRaising) {
			isRaising = true;
			raiseArms();
		}
	}
}

bool Player::checkCollision(Ent& ent) {
	float aMaxX = aabb.maxX + pos.x;
	float aMinX = aabb.minX + pos.x;
	float aMaxZ = aabb.maxZ + pos.z;
	float aMinZ = aabb.minZ + pos.z;

	// �ﰢ�Լ� ����
	// x' = xcos(a) - ysin(a)
	// y' = xsin(a) + ycos(a)
	float radian = getPlayerAngle() / 360.0 * 3.14;

	float p1X = aMaxX * cos(radian) - aMaxZ * sin(radian);
	float p1Z = aMaxX * sin(radian) + aMaxZ * cos(radian);
	float p2X = aMaxX * cos(radian) - aMinZ * sin(radian);
	float p2Z = aMaxX * sin(radian) + aMinZ * cos(radian);
	float p3X = aMinX * cos(radian) - aMaxZ * sin(radian);
	float p3Z = aMinX * sin(radian) + aMaxZ * cos(radian);
	float p4X = aMinX * cos(radian) - aMinZ * sin(radian);
	float p4Z = aMinX * sin(radian) + aMinZ * cos(radian);

	float bMaxX = ent.getAabb().maxX + ent.getPos().x;
	float bMinX = ent.getAabb().minX + ent.getPos().x;
	float bMaxZ = ent.getAabb().maxZ + ent.getPos().z;
	float bMinZ = ent.getAabb().minZ + ent.getPos().z;

	if ((bMinX < p1X && bMaxX > p1X) && (bMinZ < p1Z && bMaxZ > p1Z)) return true;
	if ((bMinX < p2X && bMaxX > p2X) && (bMinZ < p2Z && bMaxZ > p2Z)) return true;
	if ((bMinX < p3X && bMaxX > p3X) && (bMinZ < p3Z && bMaxZ > p3Z)) return true;
	if ((bMinX < p4X && bMaxX > p4X) && (bMinZ < p4Z && bMaxZ > p4Z)) return true;

	return false;
}

// --------------- actions ------------------//
void Player::rotate(float angle) {
	angles[PLAYER_ANGLE] = angle;
}

void Player::moveLeft() {
	Ent::moveLeft();
	rotate(270);
}
void Player::moveRight() {
	Ent::moveRight();
	rotate(90);
}
void Player::moveUp() {
	Ent::moveUp();
	rotate(0);
}
void Player::moveDown() {
	Ent::moveDown();
	rotate(180);
}
// �� �ø���
void Player::raiseArms() {
	if (isRaising) {
		if (angles[LEFT_ARM] < 90) { // 90�� �����̸� �ø� (90�� ���� �ø�����)
			angles[LEFT_ARM] += 1;
		}

		if (angles[RIGHT_ARM] < 90) { // 90�� �����̸� �ø� (90�� ���� �ø�����)
			angles[RIGHT_ARM] += 1;
		}

		glutPostRedisplay();

		if (angles[RIGHT_ARM] < 90 || angles[LEFT_ARM] < 90) { // �ø��� ����
			glutTimerFunc(5, raiseArmsCall, (int)this);
		}
		else { // �� �ø� ���
			isRaised = true;
			isRaising = false;
			glutTimerFunc(1000, unraiseArmTimerCall, (int)this); // 0.5�� ���� �ø��� ������ ������ �� ����
		}
	}
}

void Player::unraiseArms() {
	if (!isRaising) {
		isRaised = false;
		if (angles[LEFT_ARM] > 0) { // 0�� �̻��̸� ���� (0�� ���� ��������)
			angles[LEFT_ARM] -= 1;
		}

		if (angles[RIGHT_ARM] > 0) { // 0�� �̻��̸� ���� (0�� ���� ��������)
			angles[RIGHT_ARM] -= 1;
		}

		glutPostRedisplay();

		if (angles[RIGHT_ARM] > 0 || angles[LEFT_ARM] > 0) {
			glutTimerFunc(5, unraiseArmsCall, (int)this);
		}
	}
}

void raiseArmsCall(int p) {
	Player* player = (Player*)p;
	player->raiseArms();
}

void unraiseArmTimerCall(int p) {
	Player* player = (Player*)p;
	if (!player->getIsRaising()) {
		player->unraiseArms();
	}
}

void unraiseArmsCall(int p) {
	Player* player = (Player*)p;
	player->unraiseArms();
}