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
}

void MapState::update()
{
	pLevel->update();
}

void MapState::render()
{
	pLevel->render();
}