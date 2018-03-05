#pragma once
#include <vector>
#include "GameManager.h"
#include "Game.h"

using namespace std;

class ShopItems
{
private:
	vector<estado> shopObjects;
	Game* game;

	Texture* food;
	Texture* food2;
	Texture* WP;

public:
	ShopItems(Game* gameptr) {
		game = gameptr;
		shopObjects.resize(17);

		food = game->getTexture(4); //Item1
		food2 = game->getTexture(5);
		WP = game->getTexture(21);

		int weaponType = 0;
		int potionType = 1;
		int objectType = 2;

		shopObjects[0].empty = false;
		shopObjects[0].comprado = true;
		shopObjects[0].ID = 0;
		shopObjects[0].objects = 1;
		shopObjects[0].price = 50;
		shopObjects[0].tx = WP;
		shopObjects[0].type = weaponType; //Es un arma
		shopObjects[0].nombre = "Compas";

		shopObjects[1].empty = false;
		shopObjects[1].comprado = true;
		shopObjects[1].ID = 1;
		shopObjects[1].objects = 1;
		shopObjects[1].price = 50;
		shopObjects[1].tx = food;
		shopObjects[1].type = weaponType; //Es un arma
		shopObjects[1].nombre = "Escobilla";

		shopObjects[2].empty = false;
		shopObjects[2].comprado = true;
		shopObjects[2].ID = 2;
		shopObjects[2].objects = 1;
		shopObjects[2].price = 50;
		shopObjects[2].tx = food;
		shopObjects[2].type = weaponType; //Es un arma
		shopObjects[2].nombre = "Regla";

		shopObjects[3].empty = false;
		shopObjects[3].comprado = true;
		shopObjects[3].ID = 3;
		shopObjects[3].objects = 1;
		shopObjects[3].price = 50;
		shopObjects[3].tx = food;
		shopObjects[3].type = weaponType; //Es un arma
		shopObjects[3].nombre = "Lapiz";
	
		shopObjects[4].empty = false;
		shopObjects[4].comprado = true;
		shopObjects[4].ID = 4;
		shopObjects[4].objects = 1;
		shopObjects[4].price = 50;
		shopObjects[4].tx = food;
		shopObjects[4].type = weaponType; //Es un arma
		shopObjects[4].nombre = "Insulto";

		shopObjects[5].empty = false;
		shopObjects[5].comprado = true;
		shopObjects[5].ID = 5;
		shopObjects[5].objects = 1;
		shopObjects[5].price = 50;
		shopObjects[5].tx = food;
		shopObjects[5].type = weaponType; //Es un arma
		shopObjects[5].nombre = "Libro";

		shopObjects[6].empty = false;
		shopObjects[6].comprado = true;
		shopObjects[6].ID = 6;
		shopObjects[6].objects = 1;
		shopObjects[6].price = 50;
		shopObjects[6].tx = food;
		shopObjects[6].type = weaponType; //Es un arma
		shopObjects[6].nombre = "Pegamento";

		shopObjects[7].empty = false;
		shopObjects[7].comprado = true;
		shopObjects[7].ID = 7;
		shopObjects[7].objects = 1;
		shopObjects[7].price = 50;
		shopObjects[7].tx = food;
		shopObjects[7].type = weaponType; //Es un arma
		shopObjects[7].nombre = "Tartera";

		shopObjects[8].empty = false;
		shopObjects[8].comprado = true;
		shopObjects[8].ID = 8;
		shopObjects[8].objects = 1;
		shopObjects[8].price = 50;
		shopObjects[8].tx = food;
		shopObjects[8].type = weaponType; //Es un arma
		shopObjects[8].nombre = "Cerbatana";

		shopObjects[9].empty = false;
		shopObjects[9].comprado = true;
		shopObjects[9].ID = 9;
		shopObjects[9].objects = 1;
		shopObjects[9].price = 50;
		shopObjects[9].tx = food;
		shopObjects[9].type = weaponType; //Es un arma
		shopObjects[9].nombre = "GlobosDeAgua";

		shopObjects[10].empty = false;
		shopObjects[10].comprado = true;
		shopObjects[10].ID = 10;
		shopObjects[10].objects = 1;
		shopObjects[10].price = 50;
		shopObjects[10].tx = food;
		shopObjects[10].type = weaponType; //Es un arma
		shopObjects[10].nombre = "Tirachinas";

		shopObjects[11].empty = false;
		shopObjects[11].comprado = true;
		shopObjects[11].ID = 11;
		shopObjects[11].objects = 1;
		shopObjects[11].price = 50;
		shopObjects[11].tx = food;
		shopObjects[11].type = weaponType; //Es un arma
		shopObjects[11].nombre = "Grapadora";

		shopObjects[12].empty = false;
		shopObjects[12].comprado = true;
		shopObjects[12].ID = 12;
		shopObjects[12].objects = 1;
		shopObjects[12].price = 50;
		shopObjects[12].tx = food;
		shopObjects[12].type = weaponType; //Es un arma
		shopObjects[12].nombre = "Sacapuntas";

		shopObjects[13].empty = false;
		shopObjects[13].comprado = true;
		shopObjects[13].ID = 13;
		shopObjects[13].objects = 1;
		shopObjects[13].price = 50;
		shopObjects[13].tx = food;
		shopObjects[13].type = weaponType; //Es un arma
		shopObjects[13].nombre = "Calculadora";

		shopObjects[14].empty = false;
		shopObjects[14].comprado = true;
		shopObjects[14].ID = 14;
		shopObjects[14].objects = 1;
		shopObjects[14].price = 50;
		shopObjects[14].tx = food;
		shopObjects[14].type = weaponType; //Es un arma
		shopObjects[14].nombre = "Bandeja";

		shopObjects[15].empty = false;
		shopObjects[15].comprado = true;
		shopObjects[15].ID = 15;
		shopObjects[15].objects = 1;
		shopObjects[15].price = 50;
		shopObjects[15].tx = food;
		shopObjects[15].type = weaponType; //Es un arma
		shopObjects[15].nombre = "Borrador";

		shopObjects[16].empty = false;
		shopObjects[16].comprado = true;
		shopObjects[16].ID = 15;
		shopObjects[16].objects = 1;
		shopObjects[16].price = 100;
		shopObjects[16].tx = food2;
		shopObjects[16].type = potionType; //Es una pocion
		shopObjects[16].nombre = "Pocion de vida";
	};

	virtual ~ShopItems() {};
	vector<estado> getItems() { return shopObjects; };
};

