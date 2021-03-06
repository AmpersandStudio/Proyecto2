#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "GameManager.h"
#include "GameComponent.h"
#include "checkML.h"


enum Type { Physical, Magical, Ranged, Support };
const float TYPE_TABLE[3][3] = 
{ { 1,   2,   0.5 },
  { 2,   0.5, 1 },
  { 0.5, 1,   2 } };

struct Attack
{
	Attack() {}
	Attack(std::string n, Type t, int mp, int pp, float s, float p,
		float af, float df, float pf) : name(n), type(t), max_pp(mp), pp(pp),
		strength(s), precision(p), atk_factor(af), def_factor(df), prc_factor(pf) { }

	std::string name;
	Type type;

	int max_pp;
	int pp;

	float strength;
	float precision;

	float atk_factor;
	float def_factor;
	float prc_factor;
};

class BattleCharacter : public GameComponent
{
public:
	BattleCharacter(std::string n, Type t, float hp, float atk, float def, float prec, float vel) : name(n), type(t),
		health(hp), attack(atk), defense(def), precision(prec), velocity(vel), support(false), maxHealth(hp), attackIndex(0)
	{
		attacks.resize(4);
	}
	BattleCharacter() {}
	virtual ~BattleCharacter() {}

	Attack getAttack(int i) const { return attacks[i]; }
	std::string getName() const { return name; }
	Type getType() const { return type; }

	float getMaxHealth() const { return maxHealth; }
	float getHealth() const { return health; }
	float getAttack() const { return attack; }
	float getDefense() const { return defense; }
	float getPrecision() const { return precision; }
	float getVelocity() const { return velocity; }

	bool isSupport() const { return support; }
	bool hasTarget() const { return target; }

	void setMaxHealth(float h) { maxHealth = h; }
	void setHealth(float h) { health = h; }
	void setAttack(float a) { attack = a; }
	void setDefense(float d) { defense = d; }
	void setPrecision(float p) { precision = p; }
	void setVelocity(float v) { velocity = v; }

	void addAttack(Attack a);

	virtual bool useAttack(int i);
	void supportAttack(int i);

	bool precisionRatio(int i);
	float defenseRatio(float enemyDef);
	void criticalRatio(float& dmg);
	void typeRatio(float& dmg, int i, Type enemyType);
	void finalDamage(float& dmg, int i);
	float combat(int i, float enemyDef, Type enemyType, bool& damaged);

	virtual void receiveDamage(float dmg);
	void receiveFactors(float atk, float def, float prc);
	void setTurn(bool b) { turn_ = b; };
	bool getTurn() { return turn_; };

	float getAtkFactor() { return atkFactor; }
	float getDefFactor() { return defFactor; }
	float getPrcFactor() { return prcFactor; }

	bool isEffective() { return effective; }
	bool isNotEffective() { return notEffective; }
	bool isCritical() { return critical; }
	bool isFail() { return fail; }

	void cancelEffective() { effective = false; }
	void cancelNotEffective() { notEffective = false; }
	void cancelCritical() { critical = false; }
	void cancelFail() { fail = false; }

	virtual bool checkPP() = 0;

protected:
	std::string name;
	Type type;

	float health;
	float maxHealth;
	float attack;
	float defense;
	float precision;
	float velocity;

	float atkFactor = 1;
	float defFactor = 1;
	float prcFactor = 1;

	std::vector<Attack> attacks;
	Attack currentAttack;

	bool support;
	bool target;

	bool notEffective = false;
	bool effective = false;
	bool critical = false;
	bool fail = false;

	bool turn_ = false;
	int attackIndex;
};

