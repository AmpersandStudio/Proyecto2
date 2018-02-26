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
public:
	PlayState(Game* gamePtr);
	virtual ~PlayState();
	//EL BOTON PARA LA TIENDA
	static void toGame(Game* game);
	static void toInventary(Game* game);
};

