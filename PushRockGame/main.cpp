#include <stdlib.h>
#include <glut.h>
#include <vector>
#include "main.h"
#include "game.h"

int windowW = 500;
int windowH = 500;

void keyboardCallback(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'r':
		Game::getInstance().keyEvent(Key::RESET);
		break;
	case 'q':
		exit(0);
	default:
		break;
	}
}

void specialKeyboardCallback(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		Game::getInstance().keyEvent(Key::UP);
		break;
	case GLUT_KEY_DOWN:
		Game::getInstance().keyEvent(Key::DOWN);
		break;
	case GLUT_KEY_LEFT:
		Game::getInstance().keyEvent(Key::LEFT);
		break;
	case GLUT_KEY_RIGHT:
		Game::getInstance().keyEvent(Key::RIGHT);
		break;
	}

	glutPostRedisplay();
}

void mainPopupMenu(int entryId) {
	switch (entryId) {
	case RESTART:
		Game::getInstance().restart();
		break;
	case BEFORE_STAGE:
		Game::getInstance().beforeStage();
		break;
	}
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ���� ���� ���

	glViewport(0, 0, windowW, windowH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, (float)windowW / (float)windowH, 4.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Game::getInstance().lookAt();

	Game::getInstance().updateLight();
	
	Game::getInstance().draw();

	glutSwapBuffers();
}

void myReshape(int w, int h) {
	windowH = h;
	windowW = w;
}

void popupMenuInit() {
	int mainPopupMenuId = glutCreateMenu(mainPopupMenu);
	glutAddMenuEntry("�����", RESTART);
	glutAddMenuEntry("���� ����������", BEFORE_STAGE);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void lightInit() {
	glEnable(GL_LIGHTING); // ���� ��� Ȱ��ȭ
	glEnable(GL_LIGHT0); // 0�� ���� Ȱ��ȭ
	const GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
}

void callbackInit() {
	// Call back
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(keyboardCallback);
	glutSpecialFunc(specialKeyboardCallback);
}

void init() {
	Game::getInstance().loadStage(0);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("3D�����б� ����");

	glClearColor(0.8, 0.8, 0.8, 1.0); // �ʱ�ȭ ������ �Ͼ��

	// �ĸ�����
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	// ��������
	glEnable(GL_DEPTH_TEST);

	popupMenuInit();
	callbackInit();
	lightInit();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	init();
	glutMainLoop();
	return 0;
}