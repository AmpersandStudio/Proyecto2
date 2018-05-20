#include "IntroState.h"
#include "MainMenuState.h"
#include "StateMachine.h"

IntroState::IntroState() : firstImg(false), qbgb(false), end(false)
{
	imgs.push("qbg");
	imgs.push("intro2");
	imgs.push("intro3");
	imgs.push("intro4");
	imgs.push("intro5");
	imgs.push("intro6");

	timeStart = SDL_GetTicks();
	firstImgInterval = 4000;
	blackInterval = 14000;
	imgsInterval = 7000;

	alpha = 0;
	currentImg = "intro1";
	SoundManager::Instance()->playSound("chalk", 0);
}

IntroState::~IntroState()
{
}

bool IntroState::handleEvent(const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN ||
		event.type == SDL_MOUSEBUTTONDOWN ||
		event.type == SDL_JOYBUTTONDOWN)
	{
		toMenu();
	}
	return false;
}

void IntroState::update()
{
	if (!firstImg)
	{
		if (timeStart + firstImgInterval <= SDL_GetTicks())
		{
			firstImg = true;

			if (!imgs.empty())
			{
				currentImg = imgs.front();
				imgs.pop();
			}

			timeStart = SDL_GetTicks();

			SoundManager::Instance()->playMusic("intro", 0);
		}
	}
	else if (!qbgb)
	{
		if (timeStart + blackInterval <= SDL_GetTicks())
		{
			qbgb = true;

			if (!imgs.empty())
			{
				currentImg = imgs.front();
				imgs.pop();
			}

			timeStart = SDL_GetTicks();
		}
		else if (timeStart + 1000 <= SDL_GetTicks())
		{
			alpha++;
		}
	}
	else if (!end)
	{
		if (timeStart + imgsInterval <= SDL_GetTicks())
		{
			if (!imgs.empty())
			{
				currentImg = imgs.front();
				imgs.pop();
			}
			else
			{
				end = true;
			}

			timeStart = SDL_GetTicks();
		}
	}
	else
	{
		toMenu();
	}
}

void IntroState::render()
{
	if (!firstImg) TheTextureManager::Instance()->drawFull(currentImg, 0, 0, 800, 600, Game::Instance()->getRenderer(), 0, 255);
	else TheTextureManager::Instance()->drawFull(currentImg, 0, 0, 800, 600, Game::Instance()->getRenderer(), 0, alpha);
}

void IntroState::toMenu()
{
	SoundManager::Instance()->stopMusic();
	Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}
