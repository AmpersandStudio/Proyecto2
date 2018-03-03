#pragma once
#include "Texture.h"
#include <vector>
#include <iostream>

struct estado {
	Texture* tx;
	int price;
	bool empty,
	     comprado;
	int ID;
	int objects;
	int x,
		y,
		mX,
		mY,
		w, 
		h;
	int objectID;
	int type; //Arma = 0, pocion = 1, objeto = 2;
	string nombre;

};

using namespace std;
class GameManager
{
private:

	int money;

	vector<estado> inventory;
	

	string name;

	GameManager() {

		money = 340;

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
	void setMoney(int m) { money = m; };
	void setName(string n) { name = n;  };

};