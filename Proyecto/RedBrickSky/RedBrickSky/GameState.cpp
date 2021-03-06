#include "GameState.h"
#include "TextureManager.h"
#include "NPC.h"
#include"GameManager.h"
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
	
	SDL_RenderSetLogicalSize(Game::Instance()->getRenderer(), 800, 600);

	for (unsigned int i = 0; i < stage.size(); i++) {
		if (stage[i]->getActive())
			stage[i]->render();
	}
}

void GameState::update() {
	for (unsigned int i = 0; i < stage.size(); i++)
		if (stage[i]->getActive())
			stage[i]->update();
}

bool GameState::handleEvent(const SDL_Event& event) {
	bool capturedEvent = false;
	bool handledEvent = false;

	unsigned int i = 0;
	while (!capturedEvent && i < stage.size()) {
		if(stage[i]->getActive()) capturedEvent = stage[i]->handleEvent(event);
		handledEvent = capturedEvent;
		if (!capturedEvent) ++i;
	}
	if (event.type == SDL_QUIT) {
		Game::Instance()->exitApp();
		handledEvent = true;
	}
	return handledEvent;
}