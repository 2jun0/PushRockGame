#include "rock.h"

const Aabb Rock::ROCK_AABB = Aabb(-0.45, 0.45, -0.45, 0.45);

Rock::Rock(const Pos& pos) : Ent(ROCK_AABB, pos, EntType::ROCK) {

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