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
#include <utility>

#include "BattleEnemy.h"
#include "BattlePlayer.h"
#include "BattleCharacter.h"
#include "MouseInputForBattleComponent.h"
#include "MoveToThisPosComponent.h"

#include "checkML.h"

enum PlayerAttack {
	PINCHO_ELIPTICO, CIRCULO_PERFECTO, GOLPE_SUCIO, LIMPIEZA_FONDO, MEDIDA_EXACTA, CONVERSION_UNIDADES, ESCRIBIR_APUNTES, GARABATO,
	ALUSIONES_FAMILIARES, EXPLORAR_LUGARES, INDICE_CONFUSO, CONJURO_PAGINA, SECADO_RAPIDO, METAMATERIAL, COMIDA_PASADA, INTERCAMBIO_POSTRES,
	BOLA_PAPEL, SALIVA_CERTERA, GLOBO_AZUL, ESO_NO_AGUA, PIEDRA_SUELO, DIANA_FRENTE, GRAPAS_EXAMEN, PUNTERIA_PROFESOR,
	AFILADO_TECNICO, PRECISION_DIBUJO, DERIVAR, MEMORIA_LLENA, REFLEJO, BANDEJAZO_FINAL, POLVOS_TIZA, TEMA_NUEVO
};

enum EnemyAttack {
	PLACAJE, FINTA_LATERAL, GOLPE_BAJO, ATURDIR,
	SOPLO, VENDAVAL, CAÍDA_LIBRE, POLVAREDA,
	CONJURO, MALDICION, AS_OCULTO, PSICOSIS
};

typedef struct {
	//puntero a jugador
	//puntero a enemigo

	//BOTONES
	Button* button_0;
	Button* button_1;
	Button* button_2;
	Button* button_3;
	Button* pruebaTexto_;

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
	bool run();
	void setAttackAnim(bool b) { attackAnim_ = b; };

protected:
	battle_UI interfaz;
	bool attackMode;
	int input;
	bool Attacking_;
	bool attackAnim_;
	bool okEnemy_;
	bool okPlayer_;
	bool in = false;
	bool stopPunch = false;
	bool gotchaAnim = false;
	Vector2D iniPos;
	MoveToThisPosComponent* mc;

private:
	bool attack_;
	bool bag_;
	bool run_;

	RenderComponent* rcfade;

	GameComponent* fade_;
	int alpha_;
	bool fadeDone_;
	bool fade2Done_;

	GameComponent* fondo_;

	GameComponent* Weapon1;
	GameComponent* Weapon2;
	GameComponent* Weapon11;
	GameComponent* Weapon22;

	bool END_;

	//Creacion de la interfaz
	void createUI();
	void createCharacterInfo();
	void createBattleButtons();
	void updateVidas();

	//Actualizacion de la interfaz
	void updateVida(GameComponent* barraVida, double variacion); //Variación es el porcentaje que varía la vida en decimal (Ej: 75% es 0.75), para que la posición sea constante
	bool isButton(GameObject* object);

	//para el combate
	BattlePlayer* player = nullptr;
	BattleEnemy* enemy = nullptr;

	void constructC();
	void initC();
	void displayAttacks();
	void handleInput();

	std::vector<Attack> ataques;
	std::vector<Attack> e_ataques;
	int turno;

	void attack(int i);
	void toAttackMode();
};

