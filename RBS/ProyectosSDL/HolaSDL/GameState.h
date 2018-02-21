#pragma once
//Clase base para los estados de juego
//Tiene un stage de game objects

#include "Game.h"
#include "GameObject.h"
#include "RenderFrameComponent.h"
#include <vector>

using namespace std;

class GameState
{
protected:
	Game* game_; //puntero a juego
	vector<GameObject*> stage; //game objects del estado

public:
	GameState(Game* gamePtr); //constructora
	virtual ~GameState(); //destructora
	virtual void render(); //llama al render de cada uno de los go de su lista
	virtual void update(); //llama al update de cada uno de los go de su lista
	virtual bool handleEvent(SDL_Event& event); //llama al he de cada uno de los go de su lista
};

