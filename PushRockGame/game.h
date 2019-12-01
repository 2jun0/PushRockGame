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
	RIGHT,
	RESET,
	RESTART,
};

class Game {
private:
	static Game* myInstance;
	Player* player;
	map<EntType, vector<Ent*>*> entities;
	int mapH;
	int mapW;
	int stageIdx;
	bool isGameClear;
public:
	static const float GROUND_COLOR[];
	static EntType ENTITY_Y_INDEX[];
private:
	Game();
public:
	static  Game& getInstance();
	void restart();

	void loadStage(const int& stageIdx);
	void loadGameClearStage();
	void nextStage();
	void beforeStage();
	
	bool checkCollision(Ent* ent);
	Ent* getCollisionEntity(Ent* ent, const EntType& type);

	void addEntity(Ent* ent);
	vector<Ent*>* getEntities(const EntType& type);

	bool checkAllButtonPressed();

	void draw();
	void drawGround();
	void drawEntities();
	void drawGameClear();
	void drawMiniMap();

	void updateLight();
	void lookAt();
	void keyEvent(const Key& key);

	int getMapWidth();
	int getMapHeight();
	bool getIsGameClear();
};