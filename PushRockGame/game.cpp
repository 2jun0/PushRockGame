#include <stdlib.h>
#include "game.h"
#include "ent_factory.h"

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
}

// 스테이지 로드
void Game::loadStage(const int& stageIdx) {
	entities.clear(); // 맵의 모든 엔티티 삭제

	string stage = STAGES[stageIdx];
	char* context;

	char* token = strtok_s((char*)stage.c_str(), " ", &context);

	EntFactory factory = EntFactory();

	int z = 0, x = 0;
	while (token != NULL) {
		if(strcmp(token, "\n") == 0) {
			z++;
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
}

void Game::lookAt() {
	Pos& pos = player->getPos();

	gluLookAt(pos.x, pos.y+5, pos.z-1, pos.x, pos.y, pos.z-1,0,0,1);
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
					return true;
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