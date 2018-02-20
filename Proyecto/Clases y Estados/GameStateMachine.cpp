#include "GameStateMachine.h"



GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
}

void GameStateMachine::pushState(GameState* gs) {
	gameStates.push(gs);
}

void GameStateMachine::popState() {
	if (!gameStates.empty()) {
		delete gameStates.top();
		gameStates.pop();
	}
}

void GameStateMachine::changeState(GameState* gs) {
	popState();
	pushState(gs);
}

void GameStateMachine::clearStack() {
	while (!gameStates.empty()) {
		popState();
	}
}

GameState* GameStateMachine::currentState() {
	return (gameStates.top());
}