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
	int potions_ = 0;
	int potionsPrize = 100;

	int playerType = 0;
	int playerAttack = 12;
	int playerDeffense = 12;
	int playerSpeed = 12;
	int playerHP = 260;
	int playerMaxHP = 260;
	string name;
	string atSound;

	std::vector<bool> doors;
	int level_;
	bool gameOver_;

	bool dialogueActive;
	Interactuable* currentInter;
	Dialogue* currentDialogue_;

	bool ampersand_ = false;
	bool easterEgg[4] = { false, false, false, false };
	bool charlie_ = false;

	bool first_ = false;
	bool question_ = false;
	bool last_ = false;

	bool endGame_;

	GameManager() 
	{
		doors.resize(30);

		money = 500;

		dialogueActive = false;
		currentDialogue_ = nullptr;
		gameOver_ = false;

		name = "";

		currentInter = nullptr;

		level_ = TUTORIAL;

		first_ = false;
		question_ = false;
		last_ = false;
		endGame_ = false;
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

	enum Levels { TUTORIAL, JARDINES_INFERIORES, PASILLOS, JARDINES_SUPERIORES, GIMNASIO, CLASES, TIENDA, PASILLO_FINAL };

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

	//Metodos para los dialogos
	bool getDialogueState() { return dialogueActive; };
	void setDialogueState(bool set, Dialogue* d) { dialogueActive = set; currentDialogue_ = d; };
	Dialogue* getDialogueCurrent() { return currentDialogue_; };
	void getInteractuable(Interactuable* n) { currentInter = n; }

	//Metodos para el BattleState
	void exitBattle();
	void toBattle(int id);
	int getEnemy();
	void setAttackSound(string s) { atSound = s; };
	string getAttackSound() { return atSound; };
	inline bool getGameOver() const { return gameOver_; }
	inline void setGameOver(bool b) { gameOver_ = b; }
	inline bool getEnd() const { return endGame_; }
	inline void setEnd(bool b) { endGame_ = b; }

	//Metodos para el mapa
	int getLevel() { return level_; }
	void setCurrentLevel(int l) { level_ = l; }
	void setDoor(int keyId) { doors[keyId] = true; }
    bool getDoor(int keyId) const { return doors.at(keyId); }

	//Metodos para las pociones
	void addPotion() { potions_++; }
	int getPotions() { return potions_; }
	void setPotions(int p) { potions_ = p; }
	int getPotionsPrize() { return potionsPrize; };

	//Metodos para el Easter Egg
	void setEasterEgg(int i) { easterEgg[i] = true; }
	bool checkEasterEgg();
	void setAmpersand();
	inline bool getAmpersand() const { return ampersand_; }

	inline bool getCharlie() const { return charlie_; }
	inline void toggleCharlie() { charlie_ = !charlie_; SoundManager::Instance()->playSound("select", 0); }

	//Metodos para el personaje
	void setName(string n) { name = n; };
	void setBattlePlayer(int t, int atk, int def, int spd, int hp);
	inline int getPlayerType() const { return playerType; }
	inline int getPlayerAttack() const { return playerAttack; }
	inline int getPlayerDeffense() const { return playerDeffense; }
	inline int getPlayerSpeed() const { return playerSpeed; }
	inline int getHealth() { return playerHP; };
	inline int getMaxHealth() { return playerMaxHP; };
	inline void addPlayerAttack(int a) { playerAttack += a; }
	inline void addPlayerDeffense(int d) { playerDeffense += d; }
	inline void addPlayerSpeed(int s) { playerSpeed += s; }
	inline void addPlayerHealth(int h) { playerMaxHP += h; }
	inline void setHealth(int h) { playerHP = h; };
	inline void setMaxHealth(int h) { playerMaxHP = h; };
	inline void setPlayerAttack(int pa) { playerAttack = pa; };
	inline void setPlayerDeffense(int pd) { playerDeffense = pd; };

	//Metodos para el QuestionState
	inline bool getFirst() const { return first_; }
	inline bool getLast() const { return last_; }
	inline bool getQuestion() const { return question_; }
	inline void setFirst(bool b) { first_ = b; }
	inline void setLast(bool b) { last_ = b; }
	inline void setQuestion(bool b) { question_ = b; }

	void resetGame();
	void toLevel2();
};