#include <glut.h>
#include <vector>
#include "ent.h"
#include "game.h"

using namespace std;

int windowW = 500;
int windowH = 500;

void drawEntity(Ent ent) {
	// draw Entity
	switch (ent.type)
	{
	case WALL:
		break;
	case ROCK:
		break;
	case PLAYER:
		break;
	case BUTTON:
		break;
	case DOOR:
		break;
	default:
		break;
	}
}

void myDisplay() {
	glClearColor(1.0, 1.0, 1.0, 1.0); // �ʱ�ȭ ������ �Ͼ��
	glClear(GL_COLOR_BUFFER_BIT); // ���� ���� ���

	// ��ƼƼ ���� �׸�
	for (int i = 0; i < entities.size(); i++) {
		drawEntity(entities[i]);
	}
}

void init() {
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("3D�����б� ����");
	glutDisplayFunc(myDisplay);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	init();
	glutMainLoop();
	return 0;
}