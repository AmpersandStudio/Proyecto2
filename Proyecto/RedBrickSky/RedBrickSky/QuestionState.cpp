#include "QuestionState.h"
#include "GameManager.h"
#include "Game.h"
#include "PlayState.h"
#include "StateMachine.h"
#include "KeyInputComponentButton.h"
#include "MouseInputComponentButton.h"

#include <algorithm>

int QuestionState::cont_ = 0;
int QuestionState::physicFactor_ = 0;
int QuestionState::magicFactor_ = 0;
int QuestionState::flyingFactor_ = 0;


QuestionState::QuestionState()
{
	started_ = false;
	final_ = false;
	load_ = false;

	TheSoundManager::Instance()->stopMusic();
	TheSoundManager::Instance()->playSound("newgame", 0);

	if (XboxController::Instance()->getNumControllers() != 0)
		SDL_ShowCursor(0);
	else
		SDL_ShowCursor(1);

	createInit();
	createQuestions();

	finalType_ = 0;

	if (XboxController::Instance()->getNumControllers() == 0) //SOLO UN MANDO
		XboxController::Instance()->insertController();
}

QuestionState::~QuestionState()
{

}


void QuestionState::update()
{
	if (GameManager::Instance()->getFirst())
	{
		// Si pasamos de la pantalla inicial del estado, desactivamos los botones iniciales
		yes->setActive(false);
		no->setActive(false);

		if (cont_ == 0)
		{
			questions_.at(cont_).answer1->setActive(true);
			questions_.at(cont_).answer2->setActive(true);
			questions_.at(cont_).answer3->setActive(true);
		}
	}

	if (GameManager::Instance()->getQuestion())
	{
		// Si contestamos a una pregunta, desactivamos sus respuestas y pasamos a la siguiente
		GameManager::Instance()->setQuestion(false);
		questions_.at(cont_).answer1->setActive(false);
		questions_.at(cont_).answer2->setActive(false);
		questions_.at(cont_).answer3->setActive(false);
		cont_++;

		// Si no quedan m�s preguntas, asignamos un tipo y pasamos a la pantalla final del estado
		if (cont_ >= questions_.size())
		{
			GameManager::Instance()->setLast(true);
			assignType();
		}
		else
		{
			questions_.at(cont_).answer1->setActive(true);
			questions_.at(cont_).answer2->setActive(true);
			questions_.at(cont_).answer3->setActive(true);
		}
	}

	GameState::update();
}

void QuestionState::render()
{

	if (!GameManager::Instance()->getFirst())
	{
		TheTextureManager::Instance()->drawFull("election", 0, 0, 800, 600, Game::Instance()->getRenderer(), 0, 255);
	}
	else if (!GameManager::Instance()->getLast())
	{
		TheTextureManager::Instance()->drawFull("qbg", 0, 0, 800, 600, Game::Instance()->getRenderer(), 0, 255);
		TheTextureManager::Instance()->drawText(questions_.at(cont_).question_, TextureManager::Pixel32,
			{ 255, 255, 255, 255 }, 40, 220, Game::Instance()->getRenderer());
	}
	else
	{
		final_ = true;
		TheTextureManager::Instance()->drawFull("qbg", 0, 0, 800, 600, Game::Instance()->getRenderer(), 0, 255);
		TheTextureManager::Instance()->drawText("Siendo as�...", TextureManager::Pixel32, { 255, 255, 255, 255 },
			20, 220, Game::Instance()->getRenderer());

		switch (finalType_)
		{
		case 0:
			TheTextureManager::Instance()->drawText("Prep�rate para romper los l�mites de la realidad...", TextureManager::Pixel32, { 255, 255, 255, 255 },
				20, 250, Game::Instance()->getRenderer());
			break;


		case 1:
			TheTextureManager::Instance()->drawText("Prep�rate para entrar en un mundo m�gico...", TextureManager::Pixel32, { 255, 255, 255, 255 },
				20, 250, Game::Instance()->getRenderer());
			break;

		case 2:
			TheTextureManager::Instance()->drawText("Prep�rate para dejar volar tu imaginaci�n...", TextureManager::Pixel32, { 255, 255, 255, 255 },
				20, 250, Game::Instance()->getRenderer());
			break;
		}

	}


	GameState::render();


	if (XboxController::Instance()->getNumControllers() != 0) {

		if (started_ && !final_) {

			//A
			TheTextureManager::Instance()->drawItem("botonesXbox", 175, 425,
				70, 50, 0, 1, 1, 5, Game::Instance()->getRenderer(), 0, 255);

			//X
			TheTextureManager::Instance()->drawItem("botonesXbox", 375, 425,
				70, 50, 0, 3, 1, 5, Game::Instance()->getRenderer(), 0, 255);

			//Y
			TheTextureManager::Instance()->drawItem("botonesXbox", 590, 425,
				70, 50, 0, 4, 1, 5, Game::Instance()->getRenderer(), 0, 255);

		}

		else if (!final_) {
			//B
			TheTextureManager::Instance()->drawItem("botonesXbox", 520, 425,
				70, 50, 0, 2, 1, 5, Game::Instance()->getRenderer(), 0, 255);


			//A
			TheTextureManager::Instance()->drawItem("botonesXbox", 240, 425,
				70, 50, 0, 1, 1, 5, Game::Instance()->getRenderer(), 0, 255);
		}

		else {
			TheTextureManager::Instance()->drawItem("botonesXbox", 700, 500,
				70, 50, 0, 1, 1, 5, Game::Instance()->getRenderer(), 0, 255);
		}

	}

}

bool QuestionState::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_QUIT)
	{
		Game::Instance()->exitApp();
		return true;
	}
	else if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (GameManager::Instance()->getLast()) toGame();
	}

	else if (event.type == SDL_JOYBUTTONDOWN) {

		XboxController::Instance()->onJoystickButtonDown(event);

		if (XboxController::Instance()->getButtonState(0, 0)) { //Si se ha pulsado la A
			if (!started_) {
				beginQuestions();
				started_ = true;
			}
			else if (!final_) { addPhysic(); }

			else if (final_)
				toGame();
		}

		else if (XboxController::Instance()->getButtonState(0, 1)) {
			if (!started_)
			{
				load_ = true;
				toGame();
			}
		}
		else if (XboxController::Instance()->getButtonState(0, 2)) {
			if (started_ && !final_)
				addMagic();


		}
		else if (XboxController::Instance()->getButtonState(0, 3)) {
			if (started_ && !final_)
				addFlying();

		}

		XboxController::Instance()->onJoystickButtonUp(event); //Aseguro que levantamos el bot�n despu�s de usarlo
	}

	if (event.type == SDL_JOYBUTTONUP)
		XboxController::Instance()->onJoystickButtonUp(event);

	return GameState::handleEvent(event);
}

void QuestionState::createInit()
{
	Vector2D position0(0.85, 3.25);
	Vector2D position4(2.25, 3.25);

	double width = 200;
	double height = 100;

	// Cargamos la pantalla inicial del estado
	yes = new Button("yesbutton", beginQuestions, 0);
	no = new Button("nobutton", toGame, 0);

	yes->setPosition(position0);
	yes->setWidth(width);
	yes->setHeight(height);
	yes->addRenderComponent(new RenderFrameComponent());
	yes->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN));
	yes->addInputComponent(new MouseInputComponentButton());

	no->setPosition(position4);
	no->setWidth(width);
	no->setHeight(height);
	no->addRenderComponent(new RenderFrameComponent());
	no->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN));
	no->addInputComponent(new MouseInputComponentButton());

	stage.push_back(yes);
	stage.push_back(no);
}

void QuestionState::createQuestions()
{
	// Creamos las preguntas
	Question q1;
	q1.question_ = "�Cu�l de estas artes te emociona m�s?";
	q1.answer1 = new Button("q1_1", addPhysic, 0);
	q1.answer2 = new Button("q1_2", addMagic, 0);
	q1.answer3 = new Button("q1_3", addFlying, 0);

	Question q2;
	q2.question_ = "�En qu� universo te gustar�a vivir?";
	q2.answer1 = new Button("q2_1", addPhysic, 0);
	q2.answer2 = new Button("q2_2", addMagic, 0);
	q2.answer3 = new Button("q2_3", addFlying, 0);

	Question q3;
	q3.question_ = "�Con qu� protagonista te identificas m�s?";
	q3.answer1 = new Button("q3_1", addPhysic, 0);
	q3.answer2 = new Button("q3_2", addMagic, 0);
	q3.answer3 = new Button("q3_3", addFlying, 0);

	Question q4;
	q4.question_ = "�Qu� g�nero de juegos prefieres?";
	q4.answer1 = new Button("q4_1", addPhysic, 0);
	q4.answer2 = new Button("q4_2", addMagic, 0);
	q4.answer3 = new Button("q4_3", addFlying, 0);

	Question q5;
	q5.question_ = "�Qu� estaci�n te trae mejores recuerdos?";
	q5.answer1 = new Button("q5_1", addPhysic, 0);
	q5.answer2 = new Button("q5_2", addMagic, 0);
	q5.answer3 = new Button("q5_3", addFlying, 0);

	Question q6;
	q6.question_ = "�Qu� s�per poder elegir�as?";
	q6.answer1 = new Button("q6_1", addPhysic, 0);
	q6.answer2 = new Button("q6_2", addMagic, 0);
	q6.answer3 = new Button("q6_3", addFlying, 0);

	Question q7;
	q7.question_ = "�C�mo te definir�as sentimentalmente?";
	q7.answer1 = new Button("q7_1", addPhysic, 0);
	q7.answer2 = new Button("q7_2", addMagic, 0);
	q7.answer3 = new Button("q7_3", addFlying, 0);

	Question q8;
	q8.question_ = "�C�mo te consideras en tus relaciones?";
	q8.answer1 = new Button("q8_1", addPhysic, 0);
	q8.answer2 = new Button("q8_2", addMagic, 0);
	q8.answer3 = new Button("q8_3", addFlying, 0);

	Question q9;
	q9.question_ = "�Qu� d�as preferir�as que no se repitiesen?";
	q9.answer1 = new Button("q9_1", addPhysic, 0);
	q9.answer2 = new Button("q9_2", addMagic, 0);
	q9.answer3 = new Button("q9_3", addFlying, 0);

	Question q10;
	q10.question_ = "�Qu� tipo de persona te consideras?";
	q10.answer1 = new Button("q10_1", addPhysic, 0);
	q10.answer2 = new Button("q10_2", addMagic, 0);
	q10.answer3 = new Button("q10_3", addFlying, 0);

	Question q11;
	q11.question_ = "�A qui�n elegir�as como compa�ero de viaje?";
	q11.answer1 = new Button("q11_1", addPhysic, 0);
	q11.answer2 = new Button("q11_2", addMagic, 0);
	q11.answer3 = new Button("q11_3", addFlying, 0);

	Question q12;
	q12.question_ = "�Qu� personaje escoger�as para una aventura fant�stica?";
	q12.answer1 = new Button("q12_1", addPhysic, 0);
	q12.answer2 = new Button("q12_2", addMagic, 0);
	q12.answer3 = new Button("q12_3", addFlying, 0);


	// Creamos los botones de respuesta
	createButton(q1);
	createButton(q2);
	createButton(q3);
	createButton(q4);
	createButton(q5);
	createButton(q6);
	createButton(q7);
	createButton(q8);
	createButton(q9);
	createButton(q10);
	createButton(q11);
	createButton(q12);

	// A�adimos las preguntas a la lista
	questions_.push_back(q1);
	questions_.push_back(q2);
	questions_.push_back(q3);
	questions_.push_back(q4);
	questions_.push_back(q5);
	questions_.push_back(q6);
	questions_.push_back(q7);
	questions_.push_back(q8);
	questions_.push_back(q9);
	questions_.push_back(q10);
	questions_.push_back(q11);
	questions_.push_back(q12);
}

void QuestionState::createButton(Question q)
{
	Vector2D position1(0.50, 3);
	Vector2D position2(1.55, 3);
	Vector2D position3(2.60, 3);

	double width_a = 200;
	double height_a = 100;

	q.answer1->setPosition(position1);
	q.answer1->setWidth(width_a);
	q.answer1->setHeight(height_a);
	q.answer1->addRenderComponent(new RenderFrameComponent());
	q.answer1->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN));
	q.answer1->addInputComponent(new MouseInputComponentButton());

	q.answer2->setPosition(position2);
	q.answer2->setWidth(width_a);
	q.answer2->setHeight(height_a);
	q.answer2->addRenderComponent(new RenderFrameComponent());
	q.answer2->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN));
	q.answer2->addInputComponent(new MouseInputComponentButton());

	q.answer3->setPosition(position3);
	q.answer3->setWidth(width_a);
	q.answer3->setHeight(height_a);
	q.answer3->addRenderComponent(new RenderFrameComponent());
	q.answer3->addInputComponent(new KeyInputComponentButton(SDLK_1, SDLK_3, SDLK_2, SDLK_4, SDLK_RETURN));
	q.answer3->addInputComponent(new MouseInputComponentButton());

	q.answer1->setActive(false);
	q.answer2->setActive(false);
	q.answer3->setActive(false);

	stage.push_back(q.answer1);
	stage.push_back(q.answer2);
	stage.push_back(q.answer3);
}

void QuestionState::assignType()
{
	int ret = max(physicFactor_, max(flyingFactor_, magicFactor_));

	int t = 0, a = 12, d = 12, s = 12, h = 100;

	if (ret == physicFactor_)
	{
		t = 0;
		a = rand() % 16 + 14;
		d = rand() % 12 + 10;
		s = rand() % 14 + 12;
		h = rand() % 380 + 370;
	}
	else if (ret == magicFactor_)
	{
		t = 1;
		a = rand() % 14 + 12;
		d = rand() % 16 + 14;
		s = rand() % 12 + 10;
		h = rand() % 360 + 350;
	}
	else
	{
		t = 2;
		a = rand() % 12 + 10;
		d = rand() % 14 + 12;
		s = rand() % 16 + 14;
		h = rand() % 370 + 360;
	}

	GameManager::Instance()->setBattlePlayer(t, a, d, s, h);

	finalType_ = t;
}

void QuestionState::toGame()
{
	TheTextureManager::Instance()->drawFull("loading", 0, 0, 800, 600, Game::Instance()->getRenderer(), 0, 255);
	SDL_RenderPresent(Game::Instance()->getRenderer());
	GameManager::Instance()->setFirst(false);
	GameManager::Instance()->setQuestion(false);
	GameManager::Instance()->setLast(false);

	cont_ = 0;
	physicFactor_ = 0;
	magicFactor_ = 0;
	flyingFactor_ = 0;

	SoundManager::Instance()->playSound("select", 0);
	Game::Instance()->getStateMachine()->changeState(new PlayState());
}

void QuestionState::beginQuestions()
{
	GameManager::Instance()->setFirst(true);
	SoundManager::Instance()->playSound("select", 0);
	SoundManager::Instance()->playMusic("questions", -1);
}

void QuestionState::addPhysic()
{
	physicFactor_++;
	GameManager::Instance()->setQuestion(true);
	SoundManager::Instance()->playSound("select", 0);
}

void QuestionState::addMagic()
{
	magicFactor_++;
	GameManager::Instance()->setQuestion(true);
	SoundManager::Instance()->playSound("select", 0);
}

void QuestionState::addFlying()
{
	flyingFactor_++;
	GameManager::Instance()->setQuestion(true);
	SoundManager::Instance()->playSound("select", 0);
}