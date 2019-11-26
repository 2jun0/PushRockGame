#pragma once
#include <vector>
#include <map>
#include "stage.h"
#include "ent.h"
#include "player.h"
#include "button.h"

enum class Key {
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};

class Game {
private:
	static Game* myInstance;
	Player* player;
	map<EntType, vector<Ent*>*> entities;
public:
	static EntType ENTITY_Y_INDEX[];
private:
	Game();
public:
	static  Game& getInstance();

	void loadStage(const int& stageIdx);
	
	bool checkCollision(Ent* ent);
	Ent* getCollisionEntity(Ent* ent, const EntType& type);

	void addEntity(Ent* ent);
	vector<Ent*>* getEntities(const EntType& type);

	void drawEntities();
	void lookAt();
	void keyEvent(const Key& key);
};