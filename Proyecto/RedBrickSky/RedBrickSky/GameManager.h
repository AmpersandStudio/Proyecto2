#pragma once
#include "Texture.h"
#include <vector>
#include <iostream>
#include "GameComponent.h"

#include "checkML.h"

struct estado {
	std::string tx; //ID de la textura
	int price; //Precio, si es que se puede comprar este objeto
	bool empty, //Booleanos de control para la tienda e inventario
	     comprado;
	int ID; //ID del objeto (N�mero que se asigna al objeto cuando se crean para que todos sean diferentes)
	int objects; //control
	double x, //posiciones
		y;
	int	mX, //control para las matrices de la tienda y el inventario
		mY;
	double	w,  //ancho y alto
			h;
	int objectID; //control
	int type; //Arma = 0, pocion = 1, objeto = 2; Para asignar el tipo de objeto que es
	string nombre; // nombre del objeto
	GameComponent* GC = nullptr; //control
	int colFrame; //FIla y columna del frma
	int FilFrame;
	bool equiped = false; //Saber si el personaje lo tiene equipado o no

};

using namespace std;
class GameManager
{
private:

	int money;

	vector<estado> inventory;

	vector<bool> doors;
	

	string name;

	GameManager() {

		doors = { true, true, false };
		money = 500;

		name = "";
	}

	static GameManager* s_pInstance;

public:
	~GameManager() {};
	static GameManager* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new GameManager();
		}
		return s_pInstance;
	}

	//Metodos para el inventario
	vector<estado> copyInventory();	
	vector<bool>& getDoors() { return doors; };

	int inventorySize() { return inventory.size(); };
	void setInventory(estado t) { inventory.push_back(t); };
	void changeInventory(vector<estado> v) { inventory.clear(); inventory = v; };

	int getMoney() { return money; };
	void addMoney(int m) { money += m; };
	void setMoney(int m) { money = m; };

	void setName(string n) { name = n;  };

};