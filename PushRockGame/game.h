#pragma once
#include <vector>
#include "stage.h"
#include "ent.h"

class Game {
private:
	vector<Ent*> entities;
public:
	Game();
	void loadStage(int stageIdx);
	void drawEntities();
};