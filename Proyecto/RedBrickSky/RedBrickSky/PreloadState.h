#pragma once
#include "GameState.h"

#include "checkML.h"
class PreloadState : public GameState
{
public:
	PreloadState();
	virtual ~PreloadState();

	bool handleEvent(const SDL_Event & event);
	virtual void update();
	virtual void render();

private:
	Uint32 timeStart_;
	Uint32 timeAmpLogoInterval_;
	Uint32 timePresentInterval_;
	Uint32 timeNameInterval_;
	Uint32 timeDisplayInterval_;
	Uint32 timeTitleInterval_;

	float position_;
	float scrollOffset_;
	float speed_;
	int alpha_;
	int alphaFactor_;

	bool displayShown_;
	bool titleShown_;
	bool titleMove_;
	bool rbs_;
};

