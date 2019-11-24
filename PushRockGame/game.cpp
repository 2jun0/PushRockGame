#include <stdlib.h>
#include "game.h"
#include "ent_factory.h"

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

				entities.push_back(ent); // ��ƼƼ �迭�� ����
			}
			x++;
		}

		// next token
		token = strtok_s(NULL, " ", &context);
	}
}

void Game::drawEntities() {
	for (int i = 0; i < entities.size(); i++) {
		Ent* entity = entities[i];
		Pos& pos = entity->getPos();

		glPushMatrix();
		{
			glTranslatef(pos.x, pos.y, pos.z);
			entity->draw();
		}
		glPopMatrix();
	}
}

void Game::lookAt() {
	Pos& pos = player->getPos();

	//gluLookAt(5, 20, 5, 5, 0, 5, 0, 0, 1);
	gluLookAt(pos.x, pos.y+5, pos.z-1, pos.x, pos.y, pos.z-1,0,0,1);
}

void Game::keyEvent(const Key& key) {
	switch (key)
	{
	case Key::UP:
		player->getPos().z += 0.1;
		player->rotate(0);
		break;
	case Key::DOWN:
		player->getPos().z -= 0.1;
		player->rotate(180);
		break;
	case Key::LEFT:
		player->getPos().x += 0.1;
		player->rotate(270);
		break;
	case Key::RIGHT:
		player->getPos().x -= 0.1;
		player->rotate(90);
		break;
	}
}