#pragma once
#include "GameState.h"
#include "GameComponent.h"

class NameSelectorState : public GameState
{
private:
	GameComponent* selector_;
	GameComponent* letters_;
	string name_;
	char letters[6][9] = { { 'a','b','c','d','e','f','g','h','i' },{ 'j','k','l','m','n','ñ','o','p','q' },{ 'r','s','t','u','v','w','x','y','z' },
						   { 'A','B','C','D','E','F','G','H','I' },{ 'J','K','L','M','N','Ñ','O','P','Q' },{ 'R','S','T','U','V','W','X','Y','Z' } };

public:
	NameSelectorState();
	virtual ~NameSelectorState();
	virtual void render();
	virtual bool handleEvent(const SDL_Event& event);
};

