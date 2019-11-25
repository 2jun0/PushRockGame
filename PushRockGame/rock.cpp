#include "rock.h"

const Aabb Rock::ROCK_AABB = Aabb(-0.45, 0.45, -0.45, 0.45);

Rock::Rock(const Pos& pos) : Ent(ROCK_AABB, pos, EntType::ROCK) {

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