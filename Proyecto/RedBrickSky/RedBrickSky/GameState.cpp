#include "GameState.h"

GameState::GameState(Game* gamePtr)
{
	game_ = gamePtr;
}

GameState::~GameState()
{
	//Eliminamos memoria dinamica
	for (int i = 0; i < stage.size(); i++) {
		if (stage[i] != nullptr)
			delete stage[i];
	}
	stage.clear();
}

void GameState::render() {
	for (int i = 0; i < stage.size(); i++)
		stage[i]->render();
}

void GameState::update() {
	for (int i = 0; i < stage.size(); i++)
		stage[i]->update();
}

bool GameState::handleEvent(SDL_Event& event) {
	bool capturedEvent = false;
	bool handledEvent = false;

	int i = 0;
	while (!capturedEvent && i < stage.size()) {
		capturedEvent = stage[i]->handleEvent(event);
		handledEvent = capturedEvent;
		if (!capturedEvent) ++i;
	}
	if (event.type == SDL_QUIT) {
		game_->exitApp();
		handledEvent = true;
	}
	return handledEvent;
}