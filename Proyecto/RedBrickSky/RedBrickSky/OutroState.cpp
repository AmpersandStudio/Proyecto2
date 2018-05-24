#include "OutroState.h"
#include "CreditsState.h"
#include "StateMachine.h"
#include "XboxController.h"

OutroState::OutroState() : end(false)
{
	imgs.push("outro1");
	imgs.push("outro2");
	imgs.push("outro3");
	imgs.push("outro4");
	imgs.push("outro5");
	imgs.push("outro6");
	imgs.push("outro7");
	imgs.push("outro8");
	imgs.push("outro9");
	imgs.push("outro10");
	imgs.push("outro11");
	imgs.push("outro12"); 
	imgs.push("outro13");
	imgs.push("outro14");
	imgs.push("outro15");
	imgs.push("outro16");
	imgs.push("outro17");
	imgs.push("outro18");
	imgs.push("outro19");
	imgs.push("outro20");
	imgs.push("outro21");
	imgs.push("outro21");
	imgs.push("outro22");
	imgs.push("outro22");
	imgs.push("outro23");
	imgs.push("outro23");
	imgs.push("outro24");
	imgs.push("outro24");

	timeStart = SDL_GetTicks();
	blackInterval = 14000;
	imgsInterval = 6000;

	alpha = 0;
	currentImg = "outro1";
	SoundManager::Instance()->playMusic("outro", -1);

}

OutroState::~OutroState()
{
}

bool OutroState::handleEvent(const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN ||
		event.type == SDL_MOUSEBUTTONDOWN)
	{
		toMenu();
	}
	else if (event.type == SDL_JOYBUTTONDOWN) {

		XboxController::Instance()->onJoystickButtonDown(event);

		if (XboxController::Instance()->getButtonState(0, 1)) {
			toMenu();
		}

		XboxController::Instance()->onJoystickButtonUp(event);
	}

	else if (event.type == SDL_JOYBUTTONUP)
		XboxController::Instance()->onJoystickButtonUp(event);

	if (event.type == SDL_QUIT)
	{
		Game::Instance()->exitApp();
		return true;
	}

	return false;
}

void OutroState::update()
{
	if (!end)
	{
		if (timeStart + imgsInterval <= SDL_GetTicks())
		{
			if (!imgs.empty())
			{
				alpha = 0;
				currentImg = imgs.front();
				imgs.pop();
			}
			else
			{
				SoundManager::Instance()->playSound("chalk", 0);
				currentImg = "intro1";
				end = true;
			}

			timeStart = SDL_GetTicks();
		}
		else if (timeStart + 1000 <= SDL_GetTicks())
		{
			alpha++;
		}
	}
	else
	{
		if (timeStart + blackInterval <= SDL_GetTicks())
		{
			toMenu();
		}
	}
}

void OutroState::render()
{
	TheTextureManager::Instance()->drawFull(currentImg, 0, 0, 800, 600, Game::Instance()->getRenderer(), 0, alpha);
}

void OutroState::toMenu()
{
	SoundManager::Instance()->stopMusic();
	Game::Instance()->getStateMachine()->changeState(new CreditsState());
}
