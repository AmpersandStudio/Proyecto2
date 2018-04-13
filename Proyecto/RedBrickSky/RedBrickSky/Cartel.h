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
private:
	std::string Message;
};

class CartelCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Cartel();
	}
};
