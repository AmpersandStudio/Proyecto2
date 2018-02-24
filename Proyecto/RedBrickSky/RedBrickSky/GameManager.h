#pragma once
#include <vector>

struct estado {
	int price;
	bool empty;
	bool comprado;
	int ID;
	int objects;
	int x;
	int y;
	int mX;
	int mY;
	int w;
	int h;
	int objectID;

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
		//inventory.resize(1);

		/*inventory[0].empty = false;
		inventory[0].comprado = false;
		inventory[0].ID = 1;
		inventory[0].objects = 1;
		inventory[0].x = 2;
		inventory[0].y = 2;
		inventory[0].mX = 0;
		inventory[0].mY = 0;
		inventory[0].price = 50;*/

		/*inventory[1].empty = false;
		inventory[1].comprado = false;
		inventory[1].ID = 1;
		inventory[1].objects = 1;
		inventory[1].x = 1;
		inventory[1].y = 1;
		inventory[1].mX = 1;
		inventory[1].mY = 0;
		inventory[1].price = 50;*/
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
	void setMoney(int m) { money = m; };


};