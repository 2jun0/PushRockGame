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

// �������� �ε�
void Game::loadStage(const int& stageIdx) {
	entities.clear(); // ���� ��� ��ƼƼ ����

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
			EntType entType = (EntType)atoi(token); // ��ƼƼ Ÿ�� ����(����ȯ)
			// ��ƼƼ�� ������ (NONE�̸� �׳� �����)
			if (entType != EntType::NONE) {
				// ��ƼƼ ����
				Pos pos = Pos((float)x, 0, (float)z);	// ��ƼƼ ��ǥ

				factory.createEntity(entType, pos); // ��ƼƼ ����
				Ent* ent = factory.getEntity(); // ������ ��ƼƼ get

				if (ent->getType() == EntType::PLAYER) {
					player = (Player*)ent;
				}

				addEntity(ent); // ��ƼƼ �迭�� ����
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