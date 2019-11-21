#include <glut.h>
#include <vector>s
#include "game.h"

using namespace std;

int windowW = 500;
int windowH = 500;

Game* game;

void myDisplay() {
	glClearColor(1.0, 1.0, 1.0, 1.0); // 초기화 색깔은 하얀색
	glClear(GL_COLOR_BUFFER_BIT); // 색깔 버퍼 사용

	glMatrixMode(GL_MODELVIEW);
	game->drawEntities();
}

void init() {
	game = new Game();
	
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("3D바위밀기 게임");
	glutDisplayFunc(myDisplay);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	init();
	glutMainLoop();
	return 0;
}