#include "GameState.h"
#include "TextureManager.h"

GameState::GameState()
{
}

GameState::~GameState()
{
	//Eliminamos memoria dinamica
	for (unsigned int i = 0; i < stage.size(); i++) {
		if (stage[i] != nullptr)
			delete stage[i];
	}
	stage.clear();
}

void GameState::render() {
	
	for (unsigned int i = 0; i < stage.size(); i++)
		stage[i]->render();
}

void GameState::update() {
	for (unsigned int i = 0; i < stage.size(); i++)
		stage[i]->update();
}

bool GameState::handleEvent(const SDL_Event& event) {
	bool capturedEvent = false;
	bool handledEvent = false;

	unsigned int i = 0;
	while (!capturedEvent && i < stage.size()) {
		capturedEvent = stage[i]->handleEvent(event);
		handledEvent = capturedEvent;
		if (!capturedEvent) ++i;
	}
	if (event.type == SDL_QUIT) {
		Game::Instance()->exitApp();
		handledEvent = true;
	}
	return handledEvent;
}