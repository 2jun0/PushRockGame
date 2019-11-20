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
	glClearColor(1.0, 1.0, 1.0, 1.0); // 초기화 색깔은 하얀색
	glClear(GL_COLOR_BUFFER_BIT); // 색깔 버퍼 사용

	// 엔티티 들을 그림
	for (int i = 0; i < entities.size(); i++) {
		drawEntity(entities[i]);
	}
}

void init() {
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