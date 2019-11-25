#pragma once
#include <vector>
#include "stage.h"
#include "ent.h"
#include "player.h"

enum class Key {
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};

class Game {
private:
	vector<Ent*> entities;
	Player* player;
public:
	Game();
	void loadStage(const int& stageIdx);
	
	bool checkCollision(Ent* ent);

	void drawEntities();
	void lookAt();
	void keyEvent(const Key& key);
};