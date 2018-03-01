#pragma once

#include "BattleCharacter.h"

class BattleEnemy : public BattleCharacter
{
public:
	BattleEnemy(std::string n, Type t, float hp, float atk, float def, float prec, float vel) :
		BattleCharacter(n, t, hp, atk, def, prec, vel) {}
	virtual ~BattleEnemy();

	int selectAttack();

	virtual bool useAttack(int i);

	int getInput() const { return input; }

private:
	int input;
};

