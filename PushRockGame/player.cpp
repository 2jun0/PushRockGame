#include <cmath>
#include "player.h"

const Aabb Player::PLAYER_AABB = Aabb(-0.45, 0.45, -0.2, 0.2);

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
		glTranslatef(0.0, 0.4, 0.0); // 몸통 위치
		glRotatef(-angles[PLAYER_ANGLE], 0, 1, 0);
		// 몸통 그리기
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
			glTranslatef(0, 0.15, 0); // 어깨 위치
		
			// left arm
			glPushMatrix();
			{
				glTranslatef(-0.35, 0, 0); // 왼쪽 어깨 위치
				glRotatef(-angles[LEFT_ARM], 1, 0, 0); // 팔 돌리기
				glTranslatef(0, -0.15, 0); // 왼쪽 팔 위치
				drawArm(); // 팔 그리기
			}
			glPopMatrix();

			// right arm
			glPushMatrix();
			{
				glTranslatef(0.35, 0, 0); // 오른족 어깨 위치
				glRotatef(-angles[RIGHT_ARM], 1, 0, 0); // 팔 돌리기
				glTranslatef(0, -0.15, 0); // 오른족 팔 위치
				drawArm(); // 팔 그리기
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
bool Player::collisionEvent(Ent& ent) {
	if (ent.getType() == EntType::ROCK) {
		if (!isRaising) {
			isRaising = true;
			raiseArms();
		}
	}

	return true;
}

bool Player::checkCollision(Ent& ent) {
	return Ent::checkCollision(ent);

	//// 삼각함수 적용
	//// x' = xcos(a) - ysin(a)
	//// y' = xsin(a) + ycos(a)
	//float radian = getPlayerAngle() / 360.0 * 3.14;

	//float p1X = aabb.maxX * cos(radian) - aabb.maxZ * sin(radian) + pos.x;
	//float p1Z = aabb.maxX * sin(radian) + aabb.maxZ * cos(radian) + pos.z;
	//float p2X = aabb.maxX * cos(radian) - aabb.minZ * sin(radian) + pos.x;
	//float p2Z = aabb.maxX * sin(radian) + aabb.minZ * cos(radian) + pos.z;
	//float p3X = aabb.minX* cos(radian) - aabb.maxZ * sin(radian) + pos.x;
	//float p3Z = aabb.minX* sin(radian) + aabb.maxZ * cos(radian) + pos.z;
	//float p4X = aabb.minX* cos(radian) - aabb.minZ * sin(radian) + pos.x;
	//float p4Z = aabb.minX* sin(radian) + aabb.minZ * cos(radian) + pos.z;

	//float bMaxX = ent.getAabb().maxX + ent.getPos().x;
	//float bMinX = ent.getAabb().minX + ent.getPos().x;
	//float bMaxZ = ent.getAabb().maxZ + ent.getPos().z;
	//float bMinZ = ent.getAabb().minZ + ent.getPos().z;

	//if ((bMinX < p1X && bMaxX > p1X) && (bMinZ < p1Z && bMaxZ > p1Z)) return true;
	//if ((bMinX < p2X && bMaxX > p2X) && (bMinZ < p2Z && bMaxZ > p2Z)) return true;
	//if ((bMinX < p3X && bMaxX > p3X) && (bMinZ < p3Z && bMaxZ > p3Z)) return true;
	//if ((bMinX < p4X && bMaxX > p4X) && (bMinZ < p4Z && bMaxZ > p4Z)) return true;

	//return false;
}

// --------------- actions ------------------//
void Player::rotate(float angle) {
	angles[PLAYER_ANGLE] = angle;
}

bool Player::moveLeft() {
	rotate(270);
	return Ent::moveLeft();
}
bool Player::moveRight() {
	rotate(90);
	return Ent::moveRight();
}
bool Player::moveUp() {
	rotate(0);
	return Ent::moveUp();
}
bool Player::moveDown() {
	rotate(180);
	return Ent::moveDown();
}
// 팔 올리기
void Player::raiseArms() {
	if (isRaising) {
		if (angles[LEFT_ARM] < 90) { // 90도 이하이면 올림 (90도 까지 올릴것임)
			angles[LEFT_ARM] += 1;
		}

		if (angles[RIGHT_ARM] < 90) { // 90도 이하이면 올림 (90도 까지 올릴것임)
			angles[RIGHT_ARM] += 1;
		}

		glutPostRedisplay();

		if (angles[RIGHT_ARM] < 90 || angles[LEFT_ARM] < 90) { // 올리고 있음
			glutTimerFunc(5, raiseArmsCall, (int)this);
		}
		else { // 다 올린 경우
			isRaised = true;
			isRaising = false;
			glutTimerFunc(1000, unraiseArmTimerCall, (int)this); // 0.5초 동안 올리는 동작이 없으면 팔 내림
		}
	}
}

void Player::unraiseArms() {
	if (!isRaising) {
		isRaised = false;
		if (angles[LEFT_ARM] > 0) { // 0도 이상이면 내림 (0도 까지 내릴것임)
			angles[LEFT_ARM] -= 1;
		}

		if (angles[RIGHT_ARM] > 0) { // 0도 이상이면 내림 (0도 까지 내릴것임)
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