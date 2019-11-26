#include "rock.h"
#include "player.h"

const Aabb Rock::ROCK_AABB = Aabb(-0.45, 0.45, -0.45, 0.45);

Rock::Rock(const Pos& pos) : Ent(ROCK_AABB, pos, EntType::ROCK) {
	speed = 1;
}

void Rock::draw() {
	glPushMatrix();
	{
		glColor3f(0.5, 0.5, 0.5);
		// ����� ������ ũ��� 0.9
		// ������ ����� Rock
		glTranslatef(0.0, 0.40, 0.0); // ��ǥ���� y������ 0.45��ŭ �̴ٿ�
		glutSolidCube(0.8); // 0.9 ũ�� ��ŭ�� ������ü�� �׸���.
	}
	glPopMatrix();
}

void Rock::collisionEvent(Ent& ent) {

	// �÷��̾����׸� �и�
	if (ent.getType() == EntType::PLAYER) {
		Player& player = (Player&)ent;
		float angle = player.getPlayerAngle();

		switch ((int)angle)
		{
		case 0: // up
			moveUp();
			player.moveUp();
			break;
		case 90: // right
			moveRight();
			player.moveRight();
			break;
		case 180: // down
			moveDown();
			player.moveDown();
			break;
		case 270: // left
			moveLeft();
			player.moveLeft();
			break;
		default:
			break;
		}
	}
}