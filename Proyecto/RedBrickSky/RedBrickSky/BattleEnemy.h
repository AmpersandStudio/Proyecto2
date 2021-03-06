#pragma once

#include "BattleCharacter.h"
#include "checkML.h"

class BattleEnemy : public BattleCharacter
{
public:
	BattleEnemy(std::string n, Type t, float hp, float atk, float def, float prec, float vel) :
		BattleCharacter(n, t, hp, atk, def, prec, vel) {}
	virtual ~BattleEnemy();

	int selectAttack();

	virtual bool useAttack(int i);

	int getInput() const { return input; }

	virtual bool checkPP();

	void increasePP()
	{
		for (Attack a : attacks)
		{
			a.max_pp = 100;
			a.pp = 100;
		}
	}

private:
	int input;
};

