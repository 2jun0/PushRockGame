#include <glut.h>
#include <vector>s
#include "game.h"

using namespace std;

int windowW = 500;
int windowH = 500;

Game* game;

void myDisplay() {
	glClearColor(1.0, 1.0, 1.0, 1.0); // �ʱ�ȭ ������ �Ͼ��
	glClear(GL_COLOR_BUFFER_BIT); // ���� ���� ���

	glMatrixMode(GL_MODELVIEW);
	game->drawEntities();
}

void init() {
	game = new Game();
	
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