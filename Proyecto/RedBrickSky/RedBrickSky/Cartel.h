#pragma once
#include "Interactuable.h"
#include "checkML.h"
class Cartel :
	public Interactuable
{
public:
	Cartel();
	~Cartel();
	void activate();
	//Para establecer el mensaje si es necesario
	void setMessage(std::string msg) { Message_ = msg; };
	void setShopState(int s) { toShop = s; };
	void setTenderMan(bool s) { tenderMan = s; };
	void setToPlay(bool s) { toPlayGround = s; };
	virtual void update();

	virtual void render();
	virtual void generateCollider();
	void change();

private:
	std::string Message;
	int toShop;
	bool tenderMan;
	bool toPlayGround;
	int col_;
	bool changed_;

	Uint32 timeStart_;
	Uint32 timeNameInterval_;
	Uint32 timeDisplayInterval_;
	Uint32 timeTitleInterval_;
};

class CartelCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Cartel();
	}
};
