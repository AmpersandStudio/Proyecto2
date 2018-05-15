#pragma once

#include <queue>
#include <string>

#include "GameState.h"
#include "Button.h"

class QuestionState : public GameState
{
public:
	QuestionState();
	virtual ~QuestionState();

	virtual void update();

	struct Question
	{
		std::string question_;
		Button* answer1;
		Button* answer2;
		Button* answer3;
	};

protected:
	std::queue<Question> questions_;

	int physicFactor_;
	int magicFactor_;
	int flyingFactor_;

	inline void addPhysic() { physicFactor_++; }
	inline void addMagic() { magicFactor_++; }
	inline void addFlying() { flyingFactor_++; }

	void assignType();

	static void toGame();
	static void beginQuestions();

	void toggleButtons();

	Button* yes;
	Button* no;

	static bool first_;
};

