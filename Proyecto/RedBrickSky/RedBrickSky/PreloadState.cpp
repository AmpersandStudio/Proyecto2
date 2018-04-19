#include "PreloadState.h"
#include "TextureManager.h"
#include "Game.h"
#include "SoundManager.h"

PreloadState::PreloadState()
{
	timeStart_ = SDL_GetTicks();
	timeAmpLogoInterval_ = 3500;
	timeDisplayInterval_ = 3000;
	timePresentInterval_ = 8500;
	timeTitleInterval_ = 2800;

	scrollOffset_ = 0;
	speed_ = 12;
	alphaFactor_ = 1;
	alpha_ = 255;

	displayShown_ = false;
	titleShown_ = false;
	titleMove_ = false;
	rbs_ = false;

	SoundManager::Instance()->playMusic("departure", 0);
}


PreloadState::~PreloadState()
{
}

bool PreloadState::handleEvent(const SDL_Event & event)
{
	return GameState::handleEvent(event);
}

void PreloadState::update()
{
	if (titleMove_)
	{
		speed_++;
		alpha_--;
	}

	if (displayShown_)
	{
		scrollOffset_ += speed_;
		if (scrollOffset_ > (TheTextureManager::Instance()->getHeight("blue") - 586))
		{
			scrollOffset_ = 0;
		}
	}

	if (!displayShown_ && ((timeStart_ + timeAmpLogoInterval_) <= SDL_GetTicks()))
	{
		displayShown_ = true;
		timeStart_ = SDL_GetTicks();
	}
	
	if (displayShown_ && !titleShown_ && ((timeStart_ + timeDisplayInterval_) <= SDL_GetTicks()))
	{
		titleShown_ = true;
		timeStart_ = SDL_GetTicks();
	}

	if (titleShown_ && ((timeStart_ + timePresentInterval_) <= SDL_GetTicks()))
	{
		titleMove_ = true;
		titleShown_ = false;
		timeStart_ = SDL_GetTicks();
	}

	if (titleMove_ && ((timeStart_ + timeTitleInterval_) <= SDL_GetTicks()))
	{
		titleMove_ = false;
		rbs_ = true;
		timeStart_ = SDL_GetTicks();
	}
}

void PreloadState::render()
{
	if (displayShown_ && !titleShown_)
	{
		TheTextureManager::Instance()->drawFrame("amplogo", (TheGame::Instance()->getWinWidth() / 2) - (TheTextureManager::Instance()->getWidth("logo") / 2),
			(TheGame::Instance()->getWinHeight() / 2) - (TheTextureManager::Instance()->getHeight("logo") / 2), TheTextureManager::Instance()->getWidth("logo"), 
			TheTextureManager::Instance()->getHeight("logo"), 0, 0, TheGame::Instance()->getRenderer(), 0, 255);
	}
	if (titleShown_)
	{
		TheTextureManager::Instance()->drawFull("sky", 0, 0, TheGame::Instance()->getWinWidth(), TheGame::Instance()->getWinHeight(), TheGame::Instance()->getRenderer(), 0, 225);
		TheTextureManager::Instance()->drawScroll("blue", scrollOffset_, TheGame::Instance()->getRenderer(), SDL_FLIP_NONE);
		TheTextureManager::Instance()->drawFull("frase", 310, 150, 470, 160, TheGame::Instance()->getRenderer(), 0, 255);
	}
	if (titleMove_)
	{
		TheTextureManager::Instance()->drawFull("sky", 0, 0, TheGame::Instance()->getWinWidth(), TheGame::Instance()->getWinHeight(), TheGame::Instance()->getRenderer(), 0, 225);
		TheTextureManager::Instance()->drawScroll("blue", scrollOffset_, TheGame::Instance()->getRenderer(), SDL_FLIP_NONE);
		TheTextureManager::Instance()->drawText("A GAME DEVELOPED BY", TextureManager::CHALK24, { 255, 255, 255, 255 }, 300, 200, TheGame::Instance()->getRenderer(), SDL_FLIP_NONE, alpha_);
		TheTextureManager::Instance()->drawText("AMPERSAND STUDIO", TextureManager::CHALK24, { 255, 255, 255, 255 }, 360, 240, TheGame::Instance()->getRenderer(), SDL_FLIP_NONE, alpha_);
	}
	if (rbs_)
	{
		TheTextureManager::Instance()->drawFull("sky", 0, 0, TheGame::Instance()->getWinWidth(), TheGame::Instance()->getWinHeight(), TheGame::Instance()->getRenderer(), 0, 225);
		TheTextureManager::Instance()->drawScroll("blue", scrollOffset_, TheGame::Instance()->getRenderer(), SDL_FLIP_NONE);
		TheTextureManager::Instance()->drawFrame("logo", (TheGame::Instance()->getWinWidth() / 2) - (TheTextureManager::Instance()->getWidth("logo") / 2),
			(TheGame::Instance()->getWinHeight() / 2) - (TheTextureManager::Instance()->getHeight("logo") / 2), TheTextureManager::Instance()->getWidth("logo"), 
			TheTextureManager::Instance()->getHeight("logo"), 0, 0, TheGame::Instance()->getRenderer(), 0, 255);
	}
}
