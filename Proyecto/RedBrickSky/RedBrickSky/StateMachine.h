#pragma once
#include "GameState.h"
#include <stack>
#include "checkML.h"

class StateMachine
{
private:
	stack <GameState*> gameStates; //pila de estados de juego
public:
	StateMachine(); //constructora
	~StateMachine(); //destructora
	void pushState(GameState* gs); //mete estado en la pila
	void popState(); //quita estado de la pila
	void changeState(GameState* gs); //sustituye un estado por otro en la pila
	void clearStack(); //limpia la memoria dinamica

	const size_t& size() { return gameStates.size(); };

	GameState* currentState(); //nos da el estado actual
};
