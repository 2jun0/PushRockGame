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
		// 참고로 바위의 크기는 0.9
		// 바위는 영어로 Rock
		glTranslatef(0.0, 0.40, 0.0); // 좌표축을 y축으로 0.45만큼 이다오
		glutSolidCube(0.8); // 0.9 크기 만큼의 정육면체를 그린다.
	}
	glPopMatrix();
}

bool Rock::collisionEvent(Ent& ent) {

	// 플레이어한테만 밀림
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