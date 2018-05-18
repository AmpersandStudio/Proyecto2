#pragma once
#include "Interactuable.h"
#include "Dialogue.h"
#include "checkML.h"
class Cartel :
	public Interactuable
{
public:
	Cartel();
	~Cartel();
	void activate();

	//Para establecer el mensaje si es necesario
	void setFighter(bool set) { isFighter_ = set; };
	virtual void update();

	virtual void render();
	virtual void generateCollider();
	void change();

	void isDefeated();

	inline void setKeyID(int id) { keyID_ = id; }
	inline int getKeyID() { return keyID_; };

	void setMSG(std::string msg);

	void setId(int id) { battleId = id; }

protected:
	int col_;
	bool changed_;

	bool isFighter_ = false;
	std::string Msg_;
	Dialogue text;
	bool dialogueActive_ = false;
	bool hasDialogue = true;
	int battleId = 0;


	Uint32 timeStart_;
	Uint32 timeNameInterval_;
	Uint32 timeDisplayInterval_;
	Uint32 timeTitleInterval_;

	int keyID_;

	virtual void selectAction();
};

class CartelCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Cartel();
	}
};
