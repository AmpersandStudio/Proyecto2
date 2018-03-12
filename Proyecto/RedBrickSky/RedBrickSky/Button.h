#pragma once
#include "GameComponent.h"

typedef void CallBackOnClick();

class Button :
	public GameComponent
{
private:
	bool selected_;
	int flag_;
protected:
	CallBackOnClick* cboc_; 
	//funcion callback generica que se llamara cuando haya un click en el boton
public:
	Button(CallBackOnClick* cb, int flag);
	virtual ~Button();
	CallBackOnClick* getCallback() { return cboc_; };
	bool getSelected() { return selected_; };
	void actSelected() { selected_ = true; };
	void enableSelected() { selected_ = false; };
	int getFlag() { return flag_; };
};

