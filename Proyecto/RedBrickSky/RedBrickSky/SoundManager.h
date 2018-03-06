#pragma once

#include "SDL.h"
#include "SDL_mixer.h"

#include <iostream>
#include <map>
#include <string>

enum sound_type { SOUND_MUSIC, SOUND_SFX };

class SoundManager
{
public:

	static SoundManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new SoundManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool load(std::string fileName, std::string id, sound_type type);
	void playSound(std::string id, int loop);
	void playMusic(std::string id, int loop);
	void playSoundFood();
	void clear();

private:
	static SoundManager* s_pInstance;

	SoundManager() {}
	~SoundManager() {}

	std::map<std::string, Mix_Chunk*> m_sfxs;
	std::map<std::string, Mix_Music*> m_music;
};

typedef SoundManager TheSoundManager;