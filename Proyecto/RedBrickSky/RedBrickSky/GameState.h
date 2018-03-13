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
	vector<GameObject*> stage; //game objects del estado

public:
	GameState(); //constructora
	virtual ~GameState(); //destructora
	virtual void render(); //llama al render de cada uno de los go de su lista
	virtual void update(); //llama al update de cada uno de los go de su lista
	virtual bool handleEvent(const SDL_Event& event); //llama al he de cada uno de los go de su lista
};

