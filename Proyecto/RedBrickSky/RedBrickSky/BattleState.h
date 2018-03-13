#pragma once
#include "GameState.h"
#include "Button.h"
#include "RenderFullComponent.h"
#include "StateMachine.h"
#include "MouseInputComponentButton.h"
#include "MouseInfoClickComponent.h"
#include "GameComponent.h"
#include "Combat.h"
#include <vector>
#include <typeinfo>
#include <algorithm>

typedef struct {
	//puntero a jugador
	//puntero a enemigo

	//BOTONES
	Button* button_0;
	Button* button_1;
	Button* button_2;
	Button* button_3;

	//TEXTOS

	//BARRAS DE VIDA
	double Vida_Width = 160;
	double Vida_height = 20;

	GameComponent* UI_Vida_Player;
	Vector2D VPlayer_position;
	GameComponent* UI_Vida_Enemy;
	Vector2D VEnemy_position;

}battle_UI;

class BattleState :
	public GameState
{
public:
	BattleState();
	virtual ~BattleState();
	virtual void update();
	virtual void render();
	virtual bool handleEvent(const SDL_Event & event);
	void init();

protected:
	battle_UI interfaz;
	bool attackMode;

private:
	Combat c;

	RenderComponent* rcF; //Render Frame
	RenderComponent* rc; //Render FS
	RenderComponent* rcfade;
	InputComponent* MIC;
	InputComponent* Info;

	GameComponent* fade_;
	int alpha_;
	bool fadeDone_;
	bool fade2Done_;

	//Creacion de la interfaz
	void createUI();
	void createCharacterInfo();
	void createBattleButtons();
	void createAttackButtons();
	void updateVidas();

	//Actualizacion de la interfaz
	void updateVida(GameComponent* barraVida, double variacion); //Variación es el porcentaje que varía la vida en decimal (Ej: 75% es 0.75), para que la posición sea constante
	bool isButton(GameObject* object);

	//Acciones del menu de combate
	static void buttonsToAttack();
	static void tryEscape();
	static void usePotion();
	static void specialAttack();

	//Ataques del jugador
	static void attack1();
	static void attack2();
	static void attack3();
	static void attack4();
};

