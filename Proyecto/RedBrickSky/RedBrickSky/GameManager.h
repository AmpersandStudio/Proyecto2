#pragma once
#include "Texture.h"
#include <vector>
#include <iostream>
#include "GameComponent.h"

struct estado {
	std::string tx;
	int price;
	bool empty,
	     comprado;
	int ID;
	int objects;
	double x,
		y;
	int	mX,
		mY;
	double	w, 
			h;
	int objectID;
	int type; //Arma = 0, pocion = 1, objeto = 2;
	string nombre;
	GameComponent* GC = nullptr;
	int colFrame;
	int FilFrame;
	bool equiped = false;

};

using namespace std;
class GameManager
{
private:

	int money;

	vector<estado> inventory;
	

	string name;

	GameManager() {

		money = 500;

		name = "";
	}
	~GameManager() {};

	static GameManager* s_pInstance;

public:
	static GameManager* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new GameManager();
		}
		return s_pInstance;
	}

	//Metodos para el inventario
	vector<estado> copyInventory();	
	int inventorySize() { return inventory.size(); };
	void setInventory(estado t) { inventory.push_back(t); };
	void changeInventory(vector<estado> v) { inventory.clear(); inventory = v; };
	int getMoney() { return money; };
	void addMoney(int m) { money += m; };
	void setMoney(int m) { money = m; };
	void setName(string n) { name = n;  };

};