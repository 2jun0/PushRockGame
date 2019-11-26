#include <stdlib.h>
#include <glut.h>
#include <vector>
#include "game.h"

using namespace std;

int windowW = 500;
int windowH = 500;

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

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); // 색깔 버퍼 사용

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, (float)windowW / (float)windowH, 0, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1, 0, 0);
	Game::getInstance().lookAt();
	Game::getInstance().drawEntities();

	glutSwapBuffers();
}

void init() {
	Game::getInstance().loadStage(0);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("3D바위밀기 게임");

	glClearColor(0.8, 0.8, 0.8, 1.0); // 초기화 색깔은 하얀색

	// Call back
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(specialKeyboardCallback);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	init();
	glutMainLoop();
	return 0;
}