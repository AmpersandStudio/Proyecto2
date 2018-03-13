#pragma once
#include "GameState.h"
#include "GameComponent.h"

class PlayState :
	public GameState
{
protected:
	GameComponent* player_;

	// M�todos
	void initPlayer();
	static void toBattle();
	static void toMap();

public:
	PlayState();
	virtual ~PlayState();

	virtual bool handleEvent(const SDL_Event& event);
	//EL BOTON PARA LA TIENDA
	static void toGame();
	static void toInventary();

};

