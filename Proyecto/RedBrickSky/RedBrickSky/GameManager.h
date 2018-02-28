#pragma once
#include "Texture.h"
#include <vector>

struct estado {
	Texture* tx;
	int price;
	bool empty;
	bool comprado;
	int ID;
	int objects;
	int x;
	int y;
	int mX;
	int mY;
	int w, 
		h;
	int objectID;
	int type; //Arma = 0, pocion = 1, objeto = 2;

};

using namespace std;
class GameManager
{
private:

	int money;

	vector<estado> inventory;
	vector<estado> shopObjects;

	string name;

	GameManager() {

		money = 340;
		vector<estado> aux;
		inventory.resize(1);
		shopObjects.resize(2);

		inventory[0].empty = false;
		inventory[0].comprado = true;
		inventory[0].ID = 1;
		inventory[0].objects = 1;
		inventory[0].x = 2;
		inventory[0].y = 2;
		inventory[0].mX = 0;
		inventory[0].mY = 0;
		inventory[0].price = 50;
		inventory[0].tx = nullptr;
		inventory[0].type = 0; //Es un arma

		shopObjects[0] = inventory[0];

		shopObjects[1].empty = false;
		shopObjects[1].comprado = true;
		shopObjects[1].ID = 2;
		shopObjects[1].objects = 1;
		shopObjects[1].x = 2;
		shopObjects[1].y = 2;
		shopObjects[1].mX = 1;
		shopObjects[1].mY = 0;
		shopObjects[1].price = 100;
		shopObjects[1].tx = nullptr;
		shopObjects[1].type = 1; //Es una poción

		


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
	vector<estado> copyShopObjects();
	int inventorySize() { return inventory.size(); };
	void setInventory(estado t) { inventory.push_back(t); };
	int getMoney() { return money; };
	void setMoney(int m) { money = m; };
	void setName(string n) { name = n;  };

};