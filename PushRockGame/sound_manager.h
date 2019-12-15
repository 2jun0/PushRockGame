#pragma once
#include <string>

using namespace std;

namespace SoundRes{
	extern const string BUTTON_PRESS_WAV;
	extern const string ROCK_MOVE_WAV;
}

class SoundManager {
private:
	static SoundManager* myInstance;
private:
	SoundManager();
public:
	static SoundManager& getInstance();
	void play(string res);
};
