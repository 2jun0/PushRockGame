#pragma comment(lib, "winmm")
#include <mmstream.h>
#include"sound_manager.h"

const string SoundRes::BUTTON_PRESS_WAV = "./sound/button-press.wav";
const string SoundRes::ROCK_MOVE_WAV = "./sound/rock-move.wav";

SoundManager* SoundManager::myInstance = NULL;
SoundManager& SoundManager::getInstance() {
	if (SoundManager::myInstance == NULL) {
		SoundManager::myInstance = new SoundManager();
	}
	
	return *SoundManager::myInstance;
}

SoundManager::SoundManager() {

}

void SoundManager::play(string res) {
	PlaySound(TEXT(res.c_str()), NULL, SND_ASYNC);
}