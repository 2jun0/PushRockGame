#include "rock.h"

const Aabb Rock::ROCK_AABB = Aabb(-0.5, 0.5, -0.5, 0.5);

Rock::Rock(const Pos& pos) : Ent(ROCK_AABB, pos, EntType::ROCK) {

}

void Rock::draw() {
	glPushMatrix();
	{
		// ����� ������ ũ��� 0.9
		glTranslatef(0.0, 0.45, 0.0); // ��ǥ���� y������ 0.45��ŭ �̴ٿ�
		glutSolidCube(0.9); // 0.9 ũ�� ��ŭ�� ������ü�� �׸���.
	}
	glPopMatrix();
}