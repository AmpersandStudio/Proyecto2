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

private:
	std::string Message;
	int toShop;
	bool tenderMan;
};

class CartelCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Cartel();
	}
};
