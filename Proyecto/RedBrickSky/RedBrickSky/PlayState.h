#pragma once
#include "GameState.h"

class PlayState :
	public GameState
{
public:
	PlayState(Game* gamePtr);
	virtual ~PlayState();
	//EL BOTON PARA LA TIENDA
	static void toGame(Game* game);
};

