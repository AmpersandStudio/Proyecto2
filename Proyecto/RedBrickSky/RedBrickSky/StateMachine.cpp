#include "StateMachine.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
	clearStack();
}

void StateMachine::pushState(GameState* gs) {
	gameStates.push(gs);
}

void StateMachine::popState() {
	if (!gameStates.empty()) {
		if (gameStates.top() != nullptr) {
			delete gameStates.top();
			gameStates.pop();
		}
	}
}

void StateMachine::changeState(GameState* gs) {
	popState();
	pushState(gs);
}

void StateMachine::clearStack() {
	while (!gameStates.empty()) {
		if (gameStates.top() != nullptr) {
			delete gameStates.top();
			gameStates.pop();
		}
	}
}

GameState* StateMachine::currentState() {
	return (gameStates.top());
}


