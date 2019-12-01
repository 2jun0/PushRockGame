#include <stdlib.h>
#include "game.h"
#include "ent_factory.h"

const float Game::GROUND_COLOR[] = { 0.52, 0.35, 0.27 };

EntType Game::ENTITY_Y_INDEX[] = {
	EntType::WALL,
	EntType::BUTTON,
	EntType::ROCK,
	EntType::PLAYER
};

Game* Game::myInstance = NULL;
Game& Game::getInstance() {
	if (Game::myInstance == NULL) {
		Game::myInstance = new Game();
	}

	return *Game::myInstance;
}

Game::Game() {
	player = NULL;
	mapH = 0;
	mapW = 0;
	stageIdx = 0;
	isGameClear = false;
}

// 스테이지 로드
void Game::loadStage(const int& stageIdx) {
	entities.clear(); // 맵의 모든 엔티티 삭제
	// 맵 크기 초기화
	mapH = 0;
	mapW = 0;

	string stage = STAGES[stageIdx];

	char* context;

	char* token = strtok_s((char*)stage.c_str(), " ", &context);

	EntFactory factory = EntFactory();

	int z = 1, x = 0;
	while (token != NULL) {
		if(strcmp(token, "\n") == 0) {
			z++;
			mapW = (mapW > x) ? mapW : x;
			x = 0;
		}
		else {
			EntType entType = (EntType)atoi(token); // 엔티티 타입 구함(형변환)
			// 엔티티가 있으면 (NONE이면 그냥 빈공간)
			if (entType != EntType::NONE) {
				// 엔티티 생성
				Pos pos = Pos((float)x, 0, (float)z);	// 엔티티 좌표

				factory.createEntity(entType, pos); // 엔티티 생성
				Ent* ent = factory.getEntity(); // 생성된 엔티티 get

				if (ent->getType() == EntType::PLAYER) {
					player = (Player*)ent;
				}

				addEntity(ent); // 엔티티 배열에 저장
			}
			x++;
		}

		// next token
		token = strtok_s(NULL, " ", &context);
	}

	mapH = z;
}

void Game::loadGameClearStage() {
	entities.clear();

	player = new Player(Pos(0,0,0));
	player->superMan();
}

void Game::addEntity(Ent* ent) {
	getEntities(ent->getType())->push_back(ent);
}

vector<Ent*>* Game::getEntities(const EntType& type) {
	if (entities.count(type) == 0) {
		entities[type] = new vector<Ent*>();
	}

	return entities[type];
}

void Game::draw() {
	if (!isGameClear) {
		drawEntities();
		drawGround();
	}
	else {
		drawGameClear();
	}
}

void Game::drawGameClear() {
	player->draw();
}

void Game::drawMiniMap() {

	int n = sizeof(ENTITY_Y_INDEX) / sizeof(EntType);
	for (int typeIdx = 0; typeIdx < n; typeIdx++) {
		vector<Ent*>* v = entities[ENTITY_Y_INDEX[typeIdx]];
		for (int i = 0; i < v->size(); i++) {
			Ent* entity = (*v)[i];
			Pos& pos = entity->getPos();
			const float* color = entity->getColor();

			glPushMatrix();
			{
				glTranslatef(pos.x, pos.y+2, pos.z);
				glColor3f(color[0], color[1], color[2]);
				glutSolidCube(1);
			}
			glPopMatrix();
		}
	}
}

void Game::drawEntities() {
	int n = sizeof(ENTITY_Y_INDEX) / sizeof(EntType);
	for (int typeIdx = 0; typeIdx < n; typeIdx++) {
		vector<Ent*>* v = entities[ENTITY_Y_INDEX[typeIdx]];
		for (int i = 0; i < v->size(); i++) {
			Ent* entity = (*v)[i];
			Pos& pos = entity->getPos();

			glPushMatrix();
			{
				glTranslatef(pos.x, pos.y, pos.z);
				entity->draw();
			}
			glPopMatrix();
		}
	}

	// 모든 버튼이 눌렸는지 확인
	if (checkAllButtonPressed()) {
		// 다음 스테이지 이동!
		nextStage();
	}
}

void Game::drawGround() {
	glPushMatrix();
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, GROUND_COLOR);
		glTranslatef(mapW/2.0 - 0.5, 0, mapH/2.0 + 0.5);
		glScalef(mapW, 0, mapH);
		glutSolidCube(1);
	}
	glPopMatrix();
}

// 모든 버튼이 눌렸는지 확인하는 함수
bool Game::checkAllButtonPressed() {
	vector<Button*>* buttons = (vector<Button*>*)Game::getEntities(EntType::BUTTON);

	bool isAllPressed = (buttons->size() > 0) ? true : false;
	for (int i = 0; i < buttons->size(); i++) {
		if (!(*buttons)[i]->getIsPressed()) {
			isAllPressed = false;
			break;
		}
	}

	return isAllPressed;
}

void Game::restart() {
	isGameClear = false;
	stageIdx = 0;
	loadStage(stageIdx);
	glutPostRedisplay();
}

void Game::nextStage() {
	if (stageIdx == STAGE_COUNT-1) {
		// 이미 마지막 스테이지인 경우는 게임 클리어!
		isGameClear = true;
		stageIdx++;
		loadGameClearStage();
	}
	else {
		// 뒤에 더 있는 경우는 다음 스테이지로 이동
		stageIdx++;
		loadStage(stageIdx);
	}
}

void Game::beforeStage() {
	// 이미 처음 스테이지면, 실행 안됨!
	if (stageIdx > 0) {
		isGameClear = false;
		stageIdx--;
		loadStage(stageIdx);
		glutPostRedisplay();
	}
}

void Game::updateLight() {
	Pos& pos = player->getPos();
	float lightPos[] = {pos.x, pos.y+3, pos.z-1, 1};

	//float lightPos[] = { mapW / 2, 3, mapH / 2,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}


void Game::lookAt() {
	if (!isGameClear) {
		Pos& pos = player->getPos();
		gluLookAt(pos.x, pos.y + 5, pos.z - 1, pos.x, pos.y, pos.z - 1, 0, 0, 1);
	}
	else {
		gluLookAt(0, 5, -2, 0, 0, 0, 0, 1, 0);
	}
}

void Game::keyEvent(const Key& key) {
	switch (key)
	{
	case Key::UP:
		player->moveUp();
		break;
	case Key::DOWN:
		player->moveDown();
		break;
	case Key::LEFT:
		player->moveLeft();
		break;
	case Key::RIGHT:
		player->moveRight();
		break;
	case Key::RESET:
		loadStage(stageIdx);
		glutPostRedisplay();
		break;
	case Key::RESTART:
		stageIdx = 0;
		isGameClear = false;
		loadStage(stageIdx);
		glutPostRedisplay();
		break;
	}
}

bool Game::checkCollision(Ent* ent1) {
	int n = sizeof(ENTITY_Y_INDEX) / sizeof(EntType);
	for(int typeIdx = 0; typeIdx < n; typeIdx++) {
		vector<Ent*>* v = entities[ENTITY_Y_INDEX[typeIdx]];
		for (int i = 0; i < v->size(); i++) {
			Ent* ent = (*v)[i];

			if (ent1 != ent && (ent1->checkCollision(*ent) && ent->checkCollision(*ent1))) {
				bool c1 = ent1->collisionEvent(*ent);
				bool c2 = ent->collisionEvent(*ent1);

				if (c1 && c2) {
					ent1->afterCollisionEvent(*ent, true);
					ent->afterCollisionEvent(*ent1, true);
					return true;
				}
				else {
					ent1->afterCollisionEvent(*ent, false);
					ent->afterCollisionEvent(*ent1, false);
				}
			}
		}
	}

	return false;
}

Ent* Game::getCollisionEntity(Ent* ent1, const EntType& type) {
	vector<Ent*>* v = getEntities(type);
	for (int i = 0; i < v->size(); i++) {
		Ent* ent = (*v)[i];

		if (ent1 != ent && (ent1->checkCollision(*ent) && ent->checkCollision(*ent1))) {
			return ent;
		}
	}

	return NULL;
}

int Game::getMapWidth() {
	return mapW;
}
int Game::getMapHeight() {
	return mapH;
}

bool Game::getIsGameClear() {
	return isGameClear;
}