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

bool Rock::collisionEvent(Ent& ent) {

	// �÷��̾����׸� �и�
	if (ent.getType() == EntType::PLAYER) {
		Player& player = (Player&)ent;
		float angle = player.getPlayerAngle();

		bool isMoved;

		switch ((int)angle)
		{
		case 0: // up
			isMoved = moveUp();
			break;
		case 90: // right
			isMoved = moveRight();
			break;
		case 180: // down
			isMoved = moveDown();
			break;
		case 270: // left
			isMoved = moveLeft();
			break;
		default:
			isMoved = false;
			break;
		}

		if (isMoved) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return true;
	}
}