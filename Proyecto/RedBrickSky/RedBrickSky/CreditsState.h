#pragma once

#include "GameState.h"
#include "checkML.h"

#include <queue>
#include <string>

class CreditsState : public GameState
{
public:
	CreditsState();
	virtual ~CreditsState();

	virtual bool handleEvent(const SDL_Event & event);
	virtual void update();
	virtual void render();

private:
	Uint32 timeInit_;
	Uint32 timeStart_;
	Uint32 timeNameInterval_;
	Uint32 timeDisplayInterval_;
	Uint32 timeTitleInterval_;
	Uint32 timeTotalInterval_;

	float position_;
	float speed_;
	Uint8 alpha_;
	int alphaFactor_;

	std::queue<std::string> names_;

	bool displayShown_;
	bool titleShown_;
	bool titleMove_;
	bool nameShown_;

	void toGame();
};

