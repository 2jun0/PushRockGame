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
	static Game* myInstance;
	vector<Ent*> entities;
	Player* player;
private:
	Game();
public:
	static  Game& getInstance();

	void loadStage(const int& stageIdx);
	
	bool checkCollision(Ent* ent);

	void drawEntities();
	void lookAt();
	void keyEvent(const Key& key);
};