#pragma once

#include <queue>
#include <string>

#include "GameState.h"


class IntroState : public GameState
{
public:
	IntroState();
	virtual ~IntroState();

	virtual bool handleEvent(const SDL_Event& event);
	virtual void update();	
	virtual void render();

private:
	std::queue<std::string> imgs;
	std::string currentImg;

	bool firstImg;
	bool qbgb;
	bool end;

	int alpha;
	
	Uint32 timeStart;
	Uint32 firstImgInterval;
	Uint32 blackInterval;
	Uint32 imgsInterval;

	void toMenu();
};

