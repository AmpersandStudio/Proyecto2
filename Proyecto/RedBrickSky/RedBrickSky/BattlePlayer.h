#pragma once

#include "BattleCharacter.h"
#include "checkML.h"

class BattlePlayer : public BattleCharacter
{
public:
	BattlePlayer(std::string n, Type t, float hp, float atk, float def, float prec, float vel) :
		BattleCharacter(n, t, hp, atk, def, prec, vel) {}
	virtual ~BattlePlayer();

	virtual bool useAttack(int i);
	virtual void receiveDamage(float dmg);

	virtual bool checkPP();
};
