#pragma once
#include "GameState.h"
//Esta clase se encarga de cargar todos los recursos al comienzo del juego (sonidos, im�genes...)
class PreloadState : GameState
{
public:
	PreloadState();
	virtual ~PreloadState();
};

