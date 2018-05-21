#include "CreditsState.h"
#include "TextureManager.h"
#include "Game.h"
#include "SoundManager.h"
#include "StateMachine.h"
#include "MainMenuState.h"

CreditsState::CreditsState()
{
	SoundManager::Instance()->stopMusic();

	timeStart_ = SDL_GetTicks();
	timeDisplayInterval_ = 4500;
	timeTitleInterval_ = 7000;
	timeNameInterval_ = 6000;
	timeTotalInterval_ = 80000;

	speed_ = 0.9f;
	position_ = (TheGame::Instance()->getWinHeight() / 2) - (TheTextureManager::Instance()->getHeight("logo") / 2);
	alphaFactor_ = 1;
	alpha_ = 255;

	names_.push("MARTIN AMECHAZURRA");
	names_.push("NURIA BANGO");
	names_.push("NESTOR CABRERO");
	names_.push("JAVIER CORDERO");
	names_.push("RAUL FERNANDEZ");
	names_.push("PABLO MARTIN");
	names_.push("AARON REBOREDO");
	names_.push("JUAN RUIZ");
	names_.push("DEVELOPED BY &STUDIO");
	names_.push("THANKS FOR PLAYING!");

	displayShown_ = false;
	titleShown_ = false;
	titleMove_ = false;
	nameShown_ = false;

	timeInit_ = SDL_GetTicks();
	SoundManager::Instance()->playMusic("credits", 0);
	TextureManager::Instance()->drawFull("qbg", 0, 0, Game::Instance()->getWinWidth(), Game::Instance()->getWinHeight(), Game::Instance()->getRenderer(), 0, 255);
}

CreditsState::~CreditsState()
{
}

bool CreditsState::handleEvent(const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN ||
		event.type == SDL_MOUSEBUTTONDOWN ||
		event.type == SDL_JOYBUTTONDOWN)
	{
		toGame();
	}
	return false;
}

void CreditsState::update()
{
	if (!displayShown_ && ((timeStart_ + timeDisplayInterval_) <= SDL_GetTicks()))
	{
		displayShown_ = true;
		titleShown_ = true;
		timeStart_ = SDL_GetTicks();
	}

	if (titleShown_ && !titleMove_ && ((timeStart_ + timeTitleInterval_) <= SDL_GetTicks()))
	{
		titleMove_ = true;
	}

	if (titleMove_)
	{
		position_ -= speed_;
		if (position_ < ((TheGame::Instance()->getWinHeight() / 2) - (TheTextureManager::Instance()->getHeight("logo") / 2) - TheTextureManager::Instance()->getHeight("logo")))
		{
			titleShown_ = false;
			titleMove_ = false;
			nameShown_ = true;
			timeStart_ = SDL_GetTicks();
		}
	}

	if (displayShown_ && !titleShown_ && ((timeStart_ + timeNameInterval_) <= SDL_GetTicks()))
	{
		if(!names_.empty()) names_.pop();
		timeStart_ = SDL_GetTicks();
	}

	if (timeInit_ + timeTotalInterval_ <= SDL_GetTicks())
	{
		toGame();
	}

}

void CreditsState::render()
{
	if (displayShown_ && !names_.empty())
	{
		TheTextureManager::Instance()->drawFull("blackboard", 0, 0, TheGame::Instance()->getWinWidth(), TheGame::Instance()->getWinHeight(), TheGame::Instance()->getRenderer(), 0, alpha_);
	}

	if (titleShown_)
	{
		TheTextureManager::Instance()->drawFrame("logo", (TheGame::Instance()->getWinWidth() / 2) - (TheTextureManager::Instance()->getWidth("logo") / 2),
			position_, TheTextureManager::Instance()->getWidth("logo"), TheTextureManager::Instance()->getHeight("logo"), 0, 0, TheGame::Instance()->getRenderer(), 0, alpha_);
	}

	if (nameShown_)
	{
		if (!names_.empty()) TheTextureManager::Instance()->drawText(names_.front(), TextureManager::CHALK24, { 255, 255, 255, alpha_ }, 230, 290, TheGame::Instance()->getRenderer());
	}
}

void CreditsState::toGame()
{
	Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}
