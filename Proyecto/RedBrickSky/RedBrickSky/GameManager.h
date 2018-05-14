#pragma once
#include "Texture.h"
#include <vector>
#include <iostream>
#include "GameComponent.h"
#include "Game.h"
#include "Interactuable.h"
#include "GameState.h"

#include "checkML.h"

struct estado {
	std::string tx; //ID de la textura
	int price; //Precio, si es que se puede comprar este objeto
	bool empty, //Booleanos de control para la tienda e inventario
	     comprado;
	int ID; //ID del objeto (Número que se asigna al objeto cuando se crean para que todos sean diferentes)
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

	vector<estado> shopObjects;

	int level_;

	string name;

	bool dialogueActive;

	Interactuable* currentInter;

	Dialogue* currentDialogue_;

	bool ampersand_ = false;
	bool easterEgg[4] = { false,false, false, false };

	bool charlie_ = false;

	GameManager() 
	{
		doors.resize(30);

		money = 500;

		dialogueActive = false;
		currentDialogue_ = nullptr;

		name = "";

		currentInter = nullptr;

		level_ = CLASES;
	}

	static GameManager* s_pInstance;

	int playerHP = 350;
	int playerMaxHP = 350;

	std::vector<bool> doors;

	int potions_ = 0;

	int potionsPrize = 100;

public:
	~GameManager() {};
	static GameManager* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new GameManager();
		}
		return s_pInstance;
	}

	enum Levels { TUTORIAL, JARDINES_INFERIORES, PASILLOS, JARDINES_SUPERIORES, GIMNASIO, CLASES, TIENDA };

	//Metodos para el inventario
	vector<estado> copyInventory();	
	vector<estado> copyShopItems();

	int inventorySize() { return inventory.size(); };
	void setInventory(estado t) { inventory.push_back(t); };
	void changeInventory(vector<estado> &v) { inventory.clear(); inventory = v; };
	

	void changeShopItems(vector<estado> &v) { shopObjects.clear(); shopObjects = v; };

	int getMoney() { return money; };
	void addMoney(int m) { money += m; };
	void setMoney(int m) { money = m; };

	bool getDialogueState() { return dialogueActive; };
	void setDialogueState(bool set, Dialogue* d) { dialogueActive = set; currentDialogue_ = d; };
	Dialogue* getDialogueCurrent() { return currentDialogue_; };

	void setName(string n) { name = n;  };

	void toBattle();

	void getInteractuable(Interactuable* n) { currentInter = n; }
	void exitBattle();

	int getHealth() { return playerHP; };
	int getMaxHealth() { return playerMaxHP; };
	void setHealth(int h) { playerHP = h; };

	int getLevel() { return level_; }
	void setCurrentLevel(int l) { level_ = l; }

	void setDoor(int keyId) { doors[keyId] = true; }
    bool getDoor(int keyId) const { return doors[keyId]; }

	int getEnemy();

	void addPotion() { potions_++; }

	int getPotions() { return potions_; }
	void setPotions(int p) { potions_ = p; }

	int getPotionsPrize() { return potionsPrize; };

	void setEasterEgg(int i) { easterEgg[i] = true; }
	bool checkEasterEgg();
	void setAmpersand() { ampersand_ = true; }
	inline bool getAmpersand() const { return ampersand_; }
	inline bool getCharlie() const { return charlie_; }
	inline void toggleCharlie() { charlie_ = !charlie_; }
};