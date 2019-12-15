#include <iostream>
#include <stdlib.h>
#include <glut.h>
#include <vector>
#include "main.h"
#include "game.h"

int windowW = 500;
int windowH = 500;

void keyLog(string log) {
	cout << "Key input : " << log << endl;
}

void keyLog(unsigned char log) {
	cout << "Key input : " << log << endl;
}

void keyboardCallback(unsigned char key, int x, int y) {
	keyLog(key);
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
		keyLog("KEY UP");
		Game::getInstance().keyEvent(Key::UP);
		break;
	case GLUT_KEY_DOWN:
		keyLog("KEY DOWN");
		Game::getInstance().keyEvent(Key::DOWN);
		break;
	case GLUT_KEY_LEFT:
		keyLog("KEY LEFT");
		Game::getInstance().keyEvent(Key::LEFT);
		break;
	case GLUT_KEY_RIGHT:
		keyLog("KEY RIGHT");
		Game::getInstance().keyEvent(Key::RIGHT);
		break;
	}

	glutPostRedisplay();
}

void mainPopupMenu(int entryId) {
	switch (entryId) {
	case RESET:
		Game::getInstance().reset();
		break;
	case RESTART:
		Game::getInstance().restart();
		break;
	case BEFORE_STAGE:
		Game::getInstance().beforeStage();
		break;
	}
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 색깔 버퍼 사용

	// in game
	glViewport(0, 0, windowW, windowH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, (float)windowW / (float)windowH, 4.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Game::getInstance().lookAt();
	Game::getInstance().updateLight();
	Game::getInstance().draw();

	// minimap
	//if (!Game::getInstance().getIsGameClear()) {
	//	glDisable(GL_LIGHTING);
	//	glViewport(windowW / 3 * 2, 0, windowW / 3, windowW / 3);
	//	glMatrixMode(GL_PROJECTION);
	//	int size = Game::getInstance().getMapWidth() > Game::getInstance().getMapHeight() ? Game::getInstance().getMapWidth() : Game::getInstance().getMapHeight();
	//	glOrtho(-size, size, -size, size, -1, 1);
	//	glMatrixMode(GL_MODELVIEW);
	//	gluLookAt(Game::getInstance().getMapWidth() / 2, 3, Game::getInstance().getMapHeight() / 2, Game::getInstance().getMapWidth() / 2, 0, Game::getInstance().getMapHeight() / 2, 0, 0, 1);
	//	Game::getInstance().drawMiniMap();
	//	glEnable(GL_LIGHTING);
	//}

	glutSwapBuffers();
}

void myReshape(int w, int h) {
	windowH = h;
	windowW = w;
}

void popupMenuInit() {
	int mainPopupMenuId = glutCreateMenu(mainPopupMenu);
	glutAddMenuEntry("현재 스테이지 다시하기", RESET);
	glutAddMenuEntry("처음 스테이지로", RESTART);
	glutAddMenuEntry("이전 스테이지로", BEFORE_STAGE);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void lightInit() {
	glEnable(GL_LIGHTING); // 조명 기능 활성화
	glEnable(GL_LIGHT0); // 0번 광원 활성화
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
	glutCreateWindow("3D바위밀기 게임");

	glClearColor(0.8, 0.8, 0.8, 1.0); // 초기화 색깔은 하얀색

	// 후면제거
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	// 은면제거
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