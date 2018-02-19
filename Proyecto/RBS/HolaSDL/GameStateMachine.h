#pragma once
#include "GameState.h"
#include <stack>

using namespace std;

class GameStateMachine
{
private:
	stack <GameState*> gameStates; //pila de estados de juego
public:
	GameStateMachine(); //constructora
	~GameStateMachine(); //destructora
	void pushState(GameState* gs); //mete estado en la pila
	void popState(); //quita estado de la pila
	void changeState(GameState* gs); //sustituye un estado por otro en la pila
	void clearStack(); //limpia la memoria dinamica
	GameState* currentState(); //nos da el estado actual
};
