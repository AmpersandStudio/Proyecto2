#pragma once
#include <queue>
#include <string>
#include "GameState.h"

class OutroState :	public GameState
{
public:
	OutroState();
	virtual ~OutroState();

	virtual bool handleEvent(const SDL_Event& event);
	virtual void update();
	virtual void render();

private:
	std::queue<std::string> imgs;
	std::string currentImg;

	bool end;

	int alpha;

	Uint32 timeStart;
	Uint32 blackInterval;
	Uint32 imgsInterval;

	void toMenu();

};

