#include "BattlePlayer.h"

BattlePlayer::~BattlePlayer()
{
}

bool BattlePlayer::useAttack(int i)
{
	if (attacks[i].pp <= 0) {
		std::cout << "No quedan PP para este ataque!" << std::endl << std::endl;
		return false;
	}

	return BattleCharacter::useAttack(i);
}

void BattlePlayer::receiveDamage(float dmg)
{
	float h = GameManager::Instance()->getHealth();
	h = h - (int)dmg;
	GameManager::Instance()->setHealth(h);

	std::cout << name << " pierde " << (int)dmg << " HP!" << std::endl;
}
