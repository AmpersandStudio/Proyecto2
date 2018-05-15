#include "SoundManager.h"

SoundManager* SoundManager::s_pInstance = 0;

// Metodo para cargar musica y sonidos
bool SoundManager::load(std::string fileName, std::string id, sound_type type)
{
	if (type == SOUND_MUSIC)
	{
		Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
		if (pMusic == 0)
		{
			std::cout << "Could not load music! SDL_mixer error: " << Mix_GetError() << std::endl;
			return false;
		}

		m_music[id] = pMusic;
		return true;
	}
	else if (type == SOUND_SFX)
	{
		Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
		if (pChunk == 0)
		{
			std::cout << "Could not load SFX! SDL_mixer error: " << Mix_GetError() << std::endl;
			return false;
		}

		m_sfxs[id] = pChunk;
		return true;
	}
	return false;
}


// Metodos para reproducir musica y sonidos
void SoundManager::playMusic(std::string id, int loop)
{
	Mix_PlayMusic(m_music[id], loop);
}

void SoundManager::PlaySoundInChannel(int c, std::string id, int loop) {
	Mix_PlayChannel(c , m_sfxs[id], loop);
}

void SoundManager::playSound(std::string id, int loop)
{
	Mix_PlayChannel(-1, m_sfxs[id], loop);
}

void SoundManager::playSoundFood()
{
	if (Mix_Playing(1) == 0) Mix_PlayChannel(1, m_sfxs["food"], 0);
}

int SoundManager::isPlayingMusic() {
	return Mix_PlayingMusic();
}

//Para la ejecución de TODOS los sonidos, pero no los libera (no los borra)
void SoundManager::stopMusic() {
	Mix_HaltMusic();
}

/*Solo funciona con los SOUND_SFX.
*Valores sobre el máximo MIX_MAX_VOLUME hacen default a MIX_MAX_VOLUME
*/
void SoundManager::setChunkVolume(std::string id, int volume) {
	Mix_VolumeChunk(m_sfxs[id], volume);
}

//Volumen general de la música
void SoundManager::setMusicVolume(int volume) {
	Mix_VolumeMusic(volume);
}

//Cerrar canal
void SoundManager::closeChannel(int c) {
	Mix_HaltChannel(c);
}

bool SoundManager::isPlayingChannel(int c) {
	return Mix_Playing(c);
}

// Metodo para liberar el mapa de musica y sonido
void SoundManager::clear()
{
	m_music.clear();
	m_sfxs.clear();
	Mix_CloseAudio();

}
