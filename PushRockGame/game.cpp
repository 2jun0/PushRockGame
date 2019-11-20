#include <stdlib.h>
#include "game.h"
#include "ent_builder.h"

Game::Game() {

}

// 스테이지 로드
void Game::loadStage(int stageIdx) {
	entities.clear(); // 맵의 모든 엔티티 삭제

	string stage = STAGES[stageIdx];
	char* token = strtok((char*)stage.c_str(), " ");

	EntBuilder builder = EntBuilder();

	int y = 0, x = 0;
	while (token != NULL) {
		if(strcmp(token, "\n") == 0) {
			y++;
			x = 0;
			continue;
		}

		EntType entType = (EntType)atoi(token); // 엔티티 타입 구함(형변환)
		// 엔티티가 있으면 (NONE이면 그냥 빈공간)
		if (entType != EntType::NONE) {
			// 엔티티 생성
			Pos pos = Pos((float)x, (float)y);	// 엔티티 좌표
			builder.createEntity(entType, pos); // 엔티티 생성

			Ent* ent = builder.getEntity(); // 생성된 엔티티 get
			entities.push_back(ent); // 엔티티 배열에 저장
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