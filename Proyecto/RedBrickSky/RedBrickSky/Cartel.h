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
	void setMSG(std::string msg) { Msg_ = msg; text = Dialogue(Msg_); };
	void setFighter(bool set) { isFighter_ = set; };
	void setShopState(int s) { toShop = s; };
	void setTenderMan(bool s) { tenderMan = s; };
	void setToPlay(bool s) { toPlayGround = s; };
	virtual void update();

	virtual void render();
	virtual void generateCollider();
	void change();

	void isDefeated();

	inline void setKeyID(int id) { keyID_ = id; }
	inline void setKey(bool key) { hasKey_ = key; }
	inline int getKeyID() { return keyID_; };

private:
	int toShop;
	bool tenderMan;
	bool toPlayGround;
	int col_;
	bool changed_;

	bool isFighter_ = false;
	std::string Msg_;
	Dialogue text;
	bool dialogueActive_ = false;

	Uint32 timeStart_;
	Uint32 timeNameInterval_;
	Uint32 timeDisplayInterval_;
	Uint32 timeTitleInterval_;

	bool hasKey_;
	int keyID_;
};

class CartelCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Cartel();
	}
};
