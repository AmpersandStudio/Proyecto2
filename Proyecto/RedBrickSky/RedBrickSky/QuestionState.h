#pragma once

#include <vector>
#include <string>

#include "GameState.h"
#include "Button.h"

class QuestionState : public GameState
{
public:
	QuestionState();
	virtual ~QuestionState();

	virtual void update();
	virtual void render();
	virtual bool handleEvent(const SDL_Event& event);

	struct Question
	{
		std::string question_;
		Button* answer1;
		Button* answer2;
		Button* answer3;
	};

protected:
	std::vector<Question> questions_;

	Button* yes;
	Button* no;

	int finalType_;

	static int cont_;
	static int physicFactor_;
	static int magicFactor_;
	static int flyingFactor_;

	static void toGame();
	static void beginQuestions();
	static void addPhysic();
	static void addMagic();
	static void addFlying();

	void createInit();
	void createQuestions();
	void createButton(Question q);
	void assignType();
};

