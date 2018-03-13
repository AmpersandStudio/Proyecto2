#include "MapState.h"

MapState::MapState()
{
	cout << "Entering Map State" << endl;

	LevelParser levelParser;
	pLevel = levelParser.parseLevel("assets/provisionalTutorial.tmx");
	//pLevel = levelParser.parseLevel("assets/test.tmx");
}

MapState::~MapState()
{
	delete pLevel;
	GameState::~GameState();
}

void MapState::update()
{
	pLevel->update();
}

void MapState::render()
{
	pLevel->render();
}

bool MapState::handleEvent(const SDL_Event& event)
{
	return pLevel->getPlayer()->handleEvent(event);
}
