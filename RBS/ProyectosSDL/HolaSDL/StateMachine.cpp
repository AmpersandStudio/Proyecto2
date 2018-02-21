#include "StateMachine.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::pushState(GameState* gs) {
	gameStates.push(gs);
}

void StateMachine::popState() {
	if (!gameStates.empty()) {
		delete gameStates.top();
		gameStates.pop();
	}
}

void StateMachine::changeState(GameState* gs) {
	popState();
	pushState(gs);
}

void StateMachine::clearStack() {
	while (!gameStates.empty()) {
		popState();
	}
}

GameState* StateMachine::currentState() {
	return (gameStates.top());
}
