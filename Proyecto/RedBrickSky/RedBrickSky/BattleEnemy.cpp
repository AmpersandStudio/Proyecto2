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

int BattleEnemy::selectAttack()
{
	int i = 0;
	do {
		i = rand() % attacks.size();
	} while (attacks[i].pp <= 0);

	return i;
}
