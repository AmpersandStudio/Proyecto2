#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include "SoundManager.h"
#include "Font.h"
#include "Dialogue.h"

#include "checkML.h"

class StateMachine;
class PlayState;

class Game
{
private:
	Game();
	~Game();

	static Game s_pInstance;

	SDL_Window* WINDOW_;
	SDL_Renderer* RENDERER_;
	StateMachine* stateMachine_;

	bool error_; 
	bool exit_;

	int winWidth_;
	int winHeight_;
	int FRAME_RATE_;	

	void initSDL();
	void loadResources();
	void registerTypes();
	
public:
	static Game* Instance()	{ return &s_pInstance; }

	void begin();
	void run();
	void handleEvents();
	void update(); 
	void render();
	void clean();


	inline SDL_Renderer* getRenderer() { return RENDERER_; }
	inline SDL_Window* getWindow() { return WINDOW_; }
	inline StateMachine* getStateMachine() { return stateMachine_; }
	inline int getWinWidth() { return winWidth_; }
	inline int getWinHeight() { return winHeight_; }
	inline void exitApp() { exit_ = true; }
};

typedef Game TheGame;
