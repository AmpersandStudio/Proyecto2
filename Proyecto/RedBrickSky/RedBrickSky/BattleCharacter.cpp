#include "BattleCharacter.h"

void BattleCharacter::addAttack(Attack a)
{
	if (attackIndex > 3) {
		attackIndex = 0;
		attacks.at(attackIndex) = a;
		attackIndex++;
	}
	else
	{
		attacks.at(attackIndex) = a;
		attackIndex++;
	}
}

bool BattleCharacter::useAttack(int i)
{
	if (attacks[i].type == Support) {
		support = true;
		GameManager::Instance()->setAttackSound("golpe");
	}
	else if (attacks[i].type == Physical) GameManager::Instance()->setAttackSound("punch_2");
	else if (attacks[i].type == Ranged) GameManager::Instance()->setAttackSound("Tirachinas");
	else if (attacks[i].type == Magical) GameManager::Instance()->setAttackSound("golpe");

	if (attacks[i].name == "Ampersand")
	{
		SoundManager::Instance()->playSound("ampersand", 0);
		SDL_Delay(2500);
	}

	std::cout << name << " uso " << attacks[i].name << "!" << std::endl;
	attacks[i].pp--;
	return true;
}

void BattleCharacter::supportAttack(int i)
{
	if (attacks[i].atk_factor != 1)
	{
		attack *= attacks[i].atk_factor;

		if (attack > 2)
		{
			std::cout << "El ataque no subira mas!" << std::endl;
			attack = 2;
		}
		else
		{
			std::cout << "Subio el ataque!" << std::endl;
		}

		atkFactor = attacks[i].atk_factor;
	}

	if (attacks[i].def_factor != 1)
	{
		defense *= attacks[i].def_factor;

		if (defense > 2)
		{
			std::cout << "La defensa no subira mas!" << std::endl;
			defense = 2;
		}
		else
		{
			std::cout << "Subio la defensa!" << std::endl;
		}

		defFactor = attacks[i].def_factor;
	}

	if (attacks[i].prc_factor != 1)
	{
		precision *= attacks[i].prc_factor;

		if (precision > 2)
		{
			std::cout << "La precision no subira mas!" << std::endl;
			precision = 2;
		}
		else
		{
			std::cout << "Subio la precision!" << std::endl;
		}

		prcFactor = attacks[i].prc_factor;
	}

	support = false;
}

bool BattleCharacter::precisionRatio(int i)
{
	float prc = precision / 100;
	prc *= attacks[i].precision;
	int rnd_prc = rand() % 100;

	return ((int)prc >= rnd_prc);
}

float BattleCharacter::defenseRatio(float enemyDef)
{
	return attack / enemyDef;
}

void BattleCharacter::criticalRatio(float & dmg)
{
	int rnd_cri = rand() % 100;
	critical = false;

	if (rnd_cri <= 10) {
		std::cout << "Un golpe critico!" << std::endl;
		critical = true;
		dmg += 0.1f;
	}
}

void BattleCharacter::typeRatio(float & dmg, int i, Type enemyType)
{
	effective = false; notEffective = false;
	float type_dmg = TYPE_TABLE[attacks[i].type][enemyType];
	if (type_dmg == 2) {
		std::cout << "Es muy efectivo!" << std::endl;
		effective = true;
	}
	else if (type_dmg == 0.5) {
		std::cout << "No es muy efectivo..." << std::endl;
		notEffective = true;
	}
	dmg *= type_dmg;
}

void BattleCharacter::finalDamage(float & dmg, int i)
{
	dmg *= attacks[i].strength;
}

float BattleCharacter::combat(int i, float enemyDef, Type enemyType, bool& damaged)
{
	float dmg = 0;
	damaged = true;
	fail = false;

	target = precisionRatio(i);

	if (target)
	{
		if (support)
			supportAttack(i);
		else
		{
			dmg = defenseRatio(enemyDef);
			criticalRatio(dmg);
			typeRatio(dmg, i, enemyType);
			finalDamage(dmg, i);
		}
	}
	else
	{
		std::cout << "Pero fallo!" << std::endl;
		damaged = false;
		fail = true;
	}

	return dmg;
}

void BattleCharacter::receiveDamage(float dmg)
{
	health -= (int)dmg;

	std::cout << name << " pierde " << (int)dmg << " HP!" << std::endl;
}

void BattleCharacter::receiveFactors(float atk, float def, float prc)
{
	if (atk != 1)
	{
		attack *= atk;

		if (attack < 0.5f)
		{
			std::cout << "El ataque no bajara mas!" << std::endl;
			attack = 0.5f;
		}
		else
		{
			std::cout << "Bajo el ataque!" << std::endl;
		}

		atkFactor = atk;
	}

	if (def != 1)
	{
		defense *= def;

		if (defense < 0.5f)
		{
			std::cout << "La defensa no bajara mas!" << std::endl;
			defense = 0.5f;
		}
		else
		{
			std::cout << "Bajo la defensa!" << std::endl;
		}

		defFactor = def;
	}

	if (prc != 1)
	{
		precision *= prc;

		if (precision < 0.5f)
		{
			std::cout << "La precision no bajara mas!" << std::endl;
			precision = 0.5f;
		}
		else
		{
			std::cout << "Bajo la precision!" << std::endl;
		}

		prcFactor = prc;
	}
}
