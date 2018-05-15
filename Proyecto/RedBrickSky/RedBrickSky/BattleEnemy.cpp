#include "BattleEnemy.h"

BattleEnemy::~BattleEnemy()
{
}

bool BattleEnemy::useAttack(int i)
{
	i = selectAttack();
	input = i;
	return BattleCharacter::useAttack(input);
}

bool BattleEnemy::checkPP()
{
	int pp = 0;
	for (Attack a : attacks)
	{
		if (a.name != "") pp += a.pp;
	}
	return pp != 0;
}

int BattleEnemy::selectAttack()
{
	int i = 0;
	do {
		i = rand() % attacks.size();
	} while (attacks[i].pp <= 0);

	return i;
}
