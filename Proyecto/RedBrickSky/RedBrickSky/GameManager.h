#pragma once
#include <vector>

struct estado {
	bool empty;
	int ID;
	int objects;
	int x;
	int y;
	int mX;
	int mY;

};

using namespace std;
class GameManager
{
private:

	int money;

	vector<estado> inventory;

	GameManager() {

		money = 340;
		vector<estado> aux;
		inventory.resize(1);

		inventory[0].empty = false;
		inventory[0].ID = 1;
		inventory[0].objects = 1;
		inventory[0].x = 1;
		inventory[0].y = 1;
		inventory[0].mY = 2;
		inventory[0].mX = 2;
	}
	~GameManager();

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
	int getMoney() { return money; };


};