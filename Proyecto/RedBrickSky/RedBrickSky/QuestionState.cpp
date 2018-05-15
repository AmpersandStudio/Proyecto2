#include "QuestionState.h"
#include "GameManager.h"
#include "Game.h"
#include "PlayState.h"
#include "StateMachine.h"
#include "KeyInputComponentButton.h"
#include "MouseInputComponentButton.h"

#include <algorithm>

bool QuestionState::first_ = false;

QuestionState::QuestionState()
{
	//Question q1;
	//q1.question_ = "¿Qué obras te emocionan más?";







	// AL ENTRAR AL ESTADO
	yes = new Button("yesbutton", beginQuestions, 0);
	no = new Button("nobutton", toGame, 0);

	Vector2D position0(0.85, 2.25);
	Vector2D position3(2.25, 2.25);

	SDL_ShowCursor(1);

	double width = 200;
	double height = 100;

	yes->setPosition(position0);
	yes->setWidth(width);
	yes->setHeight(height);
	yes->addRenderComponent(new RenderFrameComponent());
	yes->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN));
	yes->addInputComponent(new MouseInputComponentButton());

	no->setPosition(position3);
	no->setWidth(width);
	no->setHeight(height);
	no->addRenderComponent(new RenderFrameComponent());
	no->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN));
	no->addInputComponent(new MouseInputComponentButton());

	stage.push_back(yes);
	stage.push_back(no);

	TheTextureManager::Instance()->drawFull("election", 0, 0, 800, 600, Game::Instance()->getRenderer(), 0, 255);
}


QuestionState::~QuestionState()
{
}

void QuestionState::update()
{
	if (first_) toggleButtons();
	GameState::update();
}

void QuestionState::assignType()
{
	int ret = max(physicFactor_, max(flyingFactor_, magicFactor_));

	int t = 0, a = 10, d = 10, s = 10, h = 300;

	if (ret == physicFactor_)
	{
		t = 0;
	}
	else if (ret == magicFactor_)
	{
		t = 1;
	}
	else
	{
		t = 2;
	}

	GameManager::Instance()->setBattlePlayer(t, a, d, s, h);
}

void QuestionState::toGame()
{
	first_ = true;
	GameManager::Instance()->setBattlePlayer(0, 12, 10, 11, 300);
	SoundManager::Instance()->playSound("select", 0);
	Game::Instance()->getStateMachine()->changeState(new PlayState());

}

void QuestionState::beginQuestions()
{
	first_ = true;
	SoundManager::Instance()->playSound("select", 0);
	SoundManager::Instance()->playMusic("questions", -1);
	TheTextureManager::Instance()->drawFull("qbg", 0, 0, 800, 600, Game::Instance()->getRenderer(), 0, 255);
}

void QuestionState::toggleButtons()
{
	yes->setActive(false);
	no->setActive(false);
}
