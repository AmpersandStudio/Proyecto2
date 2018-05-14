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
#include "MagicAttackComponent.h"

#include "checkML.h"

enum PlayerAttack {
	PINCHO_ELIPTICO, CIRCULO_PERFECTO, GOLPE_SUCIO, LIMPIEZA_FONDO, MEDIDA_EXACTA, CONVERSION_UNIDADES, ESCRIBIR_APUNTES, GARABATO,
	ALUSIONES_FAMILIARES, EXPLORAR_LUGARES, INDICE_CONFUSO, CONJURO_PAGINA, SECADO_RAPIDO, METAMATERIAL, COMIDA_PASADA, INTERCAMBIO_POSTRES,
	BOLA_PAPEL, SALIVA_CERTERA, GLOBO_AZUL, ESO_NO_AGUA, PIEDRA_SUELO, DIANA_FRENTE, GRAPAS_EXAMEN, PUNTERIA_PROFESOR, NULLPTR, AMPERSAND,
	AFILADO_TECNICO, PRECISION_DIBUJO, DERIVAR, MEMORIA_LLENA, REFLEJO, BANDEJAZO_FINAL, POLVOS_TIZA, TEMA_NUEVO, GOLPE
};

enum EnemyAttack {
	PLACAJE, FINTA_LATERAL, GOLPE_BAJO, ATURDIR,
	SOPLO, VENDAVAL, CAÍDA_LIBRE, POLVAREDA,
	CONJURO, MALDICION, AS_OCULTO, PSICOSIS
};

typedef struct {
	Button* button_0;
	Button* button_1;
	Button* button_2;
	Button* button_3;
	Button* pruebaTexto_;

} battle_UI;

class BattleState : public GameState
{
protected:
	battle_UI interfaz;

	int input;
	int alpha_;
	int W1id = 0;
	int W2id = 0;
	int turno;
	int contText = 0;
	int contTextE = 0;
	int attackPlayer = 0;
	int defensePlayer = 0;
	int precitionPlayer = 0;
	int attackEnemy = 0;
	int defenseEnemy = 0;
	int precitionEnemy = 0;

	bool attack_;
	bool bag_;
	bool run_;
	bool attackMode;
	bool Attacking_;
	bool attackAnim_;
	bool okEnemy_;
	bool okPlayer_;
	bool in = false;
	bool stopPunch = false;
	bool gotchaAnim = false;
	bool lastTurn = false;
	bool foundWP1 = false;
	bool foundWP2 = false;
	bool fadeDone_;
	bool fade2Done_;
	bool END_;
	bool weaponsEnabled_ = false;
	bool damagedE = true;
	bool damagedP = true;
	bool fail = false;
	bool keepText = false;
	bool keepTextE = false;
	bool meleeAttack = false;
	bool magicAttack = false;
	bool rangedAttack = false;
	bool potion = false;

	bool crit= false;
	bool effect = false;
	bool notEffect = false;
	bool fai = false;

	bool critE = false;
	bool effectE = false;
	bool notEffectE = false;
	bool faiE = false;

	Vector2D iniPos;
	Vector2D positionW1;
	Vector2D positionW11;
	Vector2D positionW2;
	Vector2D positionW22;

	RenderComponent* rcfade;
	MoveToThisPosComponent mcp;
	MagicAttackComponent map;
	MoveToThisPosComponent mce;
	MagicAttackComponent mae;

	GameComponent* fade_;
	GameComponent* fondo_;
	GameComponent* Weapon1;
	GameComponent* Weapon2;
	GameComponent* Weapon11;
	GameComponent* Weapon22;

	GameComponent* atqPP;
	GameComponent* atqMP;
	GameComponent* defPP;
	GameComponent* defMP;
	GameComponent* prcPP;
	GameComponent* prcMP;

	GameComponent* atqPE;
	GameComponent* atqME;
	GameComponent* defPE;
	GameComponent* defME;
	GameComponent* prcPE;
	GameComponent* prcME;

	BattlePlayer* player = nullptr;
	BattleEnemy* enemy = nullptr;

	std::vector<Attack> ataques;
	std::vector<Attack> e_ataques;

	//BLOQUES DE METODOS
	//bloque 1 (constriccion del fade inicial)
	void makeFade();

	//bloque 2 (construccion del HUD del bs)
	void createUI();
	void pickBackground();
	void createPanel();
	void createBattleButtons();
	void createCharacterInfo();
	void createStands();
	void pickArmors();

	//bloque 3 (construccion de los personajes del bs)
	void constructC();
	void createPlayer();
	void createEnemy();
	void createStatus();
	void createAttacks();
	void initC();

	//bloque 5 (auxiliares de update)
	void controlFade();
	bool run();
	void controlStatus();

	//bloque 6 (auxiliares de render)
	void updateVidas();

	//bloque 7 (auxiliares de handle events)
	void toAttackMode();
	void displayAttacks();
	void attack(int i);
	void enableWapons();
	void disableWapons();

public:
	//constructora y destructora
	//bloque 0 (constructoras y destructoras)
	BattleState();
	virtual ~BattleState();

	//metodos virtuales de gamestate
	//bloque 4 (metodos del polimorfismo)
	virtual void update();
	virtual void render();
	virtual bool handleEvent(const SDL_Event & event);

	//metodos necesariamente publicos
	//bloque 8 (metodo para la animacion)
	void setAttackAnim(bool b) { attackAnim_ = b; };
};