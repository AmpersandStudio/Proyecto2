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

	//TEXTURAS UI
	Texture* cuadro_principal;
	Texture* cuadro_personaje;
	Texture* cuadro_enemigo;
	Texture* cuadro_ataque;
	Texture* ground;
	Texture* Vida;
	Texture* botones;

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
	BattleState(Game* gamePtr);
	virtual ~BattleState();
	virtual void update();
	virtual void render();
	virtual bool handleEvent(SDL_Event & event);
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
	Game* game;

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
	static void buttonsToAttack(Game* gamePtr);
	static void tryEscape(Game* gamePtr);
	static void usePotion(Game* gamePtr);
	static void specialAttack(Game* gamePtr);

	//Ataques del jugador
	static void attack1(Game* gamePtr);
	static void attack2(Game* gamePtr);
	static void attack3(Game* gamePtr);
	static void attack4(Game* gamePtr);
};

