#pragma once
#include "GameState.h"
#include "MovableObject.h"

class PlayState :
	public GameState
{
protected:
	MovableObject* player_;


	// M�todos
	void initPlayer();
public:
	PlayState(Game* gamePtr);
	virtual ~PlayState();
	//EL BOTON PARA LA TIENDA
	static void toGame(Game* game);
};

