#include <stdlib.h>
#include "game.h"
#include "ent_builder.h"

Game::Game() {

}

// �������� �ε�
void Game::loadStage(int stageIdx) {
	entities.clear(); // ���� ��� ��ƼƼ ����

	string stage = STAGES[stageIdx];
	char* token = strtok((char*)stage.c_str(), " ");

	EntBuilder builder = EntBuilder();

	int z = 0, x = 0;
	while (token != NULL) {
		if(strcmp(token, "\n") == 0) {
			z++;
			x = 0;
			continue;
		}

		EntType entType = (EntType)atoi(token); // ��ƼƼ Ÿ�� ����(����ȯ)
		// ��ƼƼ�� ������ (NONE�̸� �׳� �����)
		if (entType != EntType::NONE) { 
			// ��ƼƼ ����
			Pos pos = Pos((float)x, 0, (float)z);	// ��ƼƼ ��ǥ
			builder.createEntity(entType, pos); // ��ƼƼ ����

			Ent* ent = builder.getEntity(); // ������ ��ƼƼ get
			entities.push_back(ent); // ��ƼƼ �迭�� ����
		}
		x++;

		// next token
		token = strtok(NULL, " ");
	}
}

void Game::drawEntities() {
	for (int i = 0; i < entities.size(); i++) {
		Ent* entity = entities.at[i];
		Pos& pos = entity->getPos();

		glPushMatrix();
		{
			glTranslatef(pos.x, pos.y, pos.z);
			entity->draw();
		}
		glPopMatrix();
	}
}