#pragma once
#include "GameState.h"
#include "GameComponent.h"

class PlayState :
	public GameState
{
protected:
	GameComponent* player_;


	// Métodos
	void initPlayer();
	static void toBattle(Game * game);
public:
	PlayState(Game* gamePtr);
	virtual ~PlayState();

	virtual bool handleEvent(SDL_Event& event);
	//EL BOTON PARA LA TIENDA
	static void toGame(Game* game);
	static void toInventary(Game* game);
};

