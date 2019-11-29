#pragma once
using namespace std;

extern int windowW;
extern int windowH;

enum MAIN_MENU_ENTRY_ID {
	RESTART = 1,
	BEFORE_STAGE
};

int main(int argc, char** argv);

void init();
void popupMenuInit();
void lightInit();
void callbackInit();

void myReshape(int w, int h);
void myDisplay();
void specialKeyboardCallback(int key, int x, int y);
void keyboardCallback(unsigned char key, int x, int y);

void mainPopupMenu(int entryId);