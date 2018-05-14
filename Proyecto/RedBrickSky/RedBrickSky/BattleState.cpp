#include "BattleState.h"
#include "TextureManager.h"
#include "RenderSingleFrameComponent.h"
#include "RenderFraemeComponent2.h"
#include "BattleCharacter.h"
#include "GameManager.h"

//bloque 0 (constructoras y destructoras) ---------------------------------------------------------------------------------
BattleState::BattleState()
{

	SDL_ShowCursor(1);

	attack_ = false;
	bag_ = false;
	run_ = false;
	okEnemy_ = false;
	okPlayer_ = true;
	END_ = false;
	Attacking_ = false;
	attackAnim_ = false;

	//fade inicial
	makeFade();
	//creamos el hud
	createUI();
}

BattleState::~BattleState()
{
	SDL_ShowCursor(0);
	SDL_SetTextureAlphaMod(TheTextureManager::Instance()->getTexture("23"), 255); //para restaurar el alpha original
	if (interfaz.button_0 != 0) delete interfaz.button_0;
	if (interfaz.button_1 != 0) delete interfaz.button_1;
	if (interfaz.button_2 != 0) delete interfaz.button_2;
	if (interfaz.button_3 != 0) delete interfaz.button_3;

	player->clearPhysicscomp();
	enemy->clearPhysicscomp();
}

//bloque 1 (constriccion del fade inicial) --------------------------------------------------------------------------------
void BattleState::makeFade() {
	rcfade = new RenderFullComponent();
	alpha_ = 255;
	fade_ = new GameComponent();
	fade_->setTextureId("23");
	fade_->addRenderComponent(rcfade);
	fadeDone_ = false;
	fade2Done_ = false;
}

//bloque 2 (construccion del HUD del bs) ----------------------------------------------------------------------------------
void BattleState::createUI() {
	//aseguramos vector limpio
	stage.clear();

	//tomamos fondo
	pickBackground();

	//panel de ataques
	createPanel();

	//botones de interaccion
	createBattleButtons();

	//cuadros de vida
	createCharacterInfo();

	//stands de los personajes
	createStands();

	//preparamos el combate
	constructC();

	//equipamos las armas
	pickArmors();

	//fade inicial
	stage.push_back(fade_);
}

void BattleState::pickBackground() {
	fondo_ = new GameComponent();

	int currLevel = GameManager::Instance()->getLevel();

	if (currLevel == 0) {
		fondo_->setTextureId("battlebg1");
	}

	else if (currLevel == 1) {
		fondo_->setTextureId("battlebg4");
	}

	else if (currLevel == 2) {
		fondo_->setTextureId("battlebg3");
	}

	else if (currLevel == 3) {
		int rnd = rand() % 2;
		switch (rnd)
		{
		case 0:
			fondo_->setTextureId("battlebg11");
			break;
		case 1:
			fondo_->setTextureId("battlebg8");
			break;

		default:
			fondo_->setTextureId("battlebg8");
			break;
		}
	}

	else if (currLevel == 4) {
		fondo_->setTextureId("battlebg2");
	}

	else if (currLevel == 5) {
		int rnd = rand() % 4;
		switch (rnd)
		{
		case 0:
			fondo_->setTextureId("battlebg9");
			break;
		case 1:
			fondo_->setTextureId("battlebg6");
			break;
		case 2:
			fondo_->setTextureId("battlebg7");
			break;
		case 3:
			fondo_->setTextureId("battlebg10");
			break;

		default:
			fondo_->setTextureId("battlebg10");
			break;
		}
	}

	else {
		fondo_->setTextureId("battlebg4");
	}

	fondo_->addRenderComponent(new RenderFullComponent());
	stage.push_back(fondo_);
}

void BattleState::createPanel() {
	Vector2D position0(0, 2.55);
	GameComponent* UI_Background = new GameComponent();
	UI_Background->setTextureId("24");
	UI_Background->setWidth(Game::Instance()->getWinWidth()); UI_Background->setHeight((170));
	UI_Background->setPosition(position0);
	UI_Background->addRenderComponent(new RenderFrameComponent());
	stage.push_back(UI_Background);
}

void BattleState::createBattleButtons()
{
	Vector2D position0;
	double buttonWidth = 170;
	double buttonHeight = 70;

	//Boton 0
	interfaz.button_0 = new Button("19", nullptr, 0);
	position0.setX(2.4); position0.setY(6.4);
	interfaz.button_0->setPosition(position0); interfaz.button_0->setWidth(buttonWidth); interfaz.button_0->setHeight(buttonHeight);
	//interfaz.button_0->addRenderComponent(rcF);
	interfaz.button_0->addInputComponent(new MouseInputForBattleComponent());
	//stage.push_back(interfaz.button_0);

	//Boton 1
	interfaz.button_1 = new Button("19", nullptr, 1);
	position0.setX(3.6); position0.setY(6.4);
	interfaz.button_1->setPosition(position0); interfaz.button_1->setWidth(buttonWidth); interfaz.button_1->setHeight(buttonHeight);
	//interfaz.button_1->addRenderComponent(rcF); 
	interfaz.button_1->addInputComponent(new MouseInputForBattleComponent());
	//stage.push_back(interfaz.button_1);

	//Boton 2
	interfaz.button_2 = new Button("19", nullptr, 2);
	position0.setX(2.4); position0.setY(7.6);
	//interfaz.button_2->addRenderComponent(rcF);
	interfaz.button_2->setPosition(position0); interfaz.button_2->setWidth(buttonWidth); interfaz.button_2->setHeight(buttonHeight);
	interfaz.button_2->addInputComponent(new MouseInputForBattleComponent());
	//stage.push_back(interfaz.button_2);

	//Boton 3
	interfaz.button_3 = new Button("19", nullptr, 3);
	position0.setX(3.6); position0.setY(7.5);
	interfaz.button_3->setPosition(position0); interfaz.button_3->setWidth(buttonWidth); interfaz.button_3->setHeight(buttonHeight);
	//interfaz.button_3->addRenderComponent(rcF); 
	interfaz.button_3->addInputComponent(new MouseInputForBattleComponent());
	//stage.push_back(interfaz.button_3);

	//Boton prueba
	interfaz.pruebaTexto_ = new Button("selOptTexto", nullptr, 4);
	position0.setX(0.15); position0.setY(4.65);
	interfaz.pruebaTexto_->setPosition(position0); interfaz.pruebaTexto_->setWidth(300); interfaz.pruebaTexto_->setHeight(100);
	interfaz.pruebaTexto_->addRenderComponent(new RenderFrameComponent());
	//interfaz.pruebaTexto_->addInputComponent(MIC);
	stage.push_back(interfaz.pruebaTexto_);
}

void BattleState::createCharacterInfo()
{
	Vector2D position0;

	//Cuadro Jugador
	GameComponent* UI_Player = new GameComponent();
	position0.setX(0.15); position0.setY(0.2);
	UI_Player->setTextureId("26");
	UI_Player->setWidth(250); UI_Player->setHeight((100));
	UI_Player->setPosition(position0);
	UI_Player->addRenderComponent(new RenderFrameComponent());
	stage.push_back(UI_Player);

	//Cuadro Enemigo
	GameComponent* UI_Enemy = new GameComponent();
	position0.setX(2.05); position0.setY(0.2);
	UI_Enemy->setTextureId("25");;
	UI_Enemy->setWidth(250); UI_Enemy->setHeight((100));
	UI_Enemy->setPosition(position0);
	UI_Enemy->addRenderComponent(new RenderFrameComponent());
	stage.push_back(UI_Enemy);
}

void BattleState::createStands() {
	GameComponent* ground = new GameComponent();
	ground->setTextureId("27");
	Vector2D pos(0.6, 1.7);
	ground->setPosition(pos);
	ground->setWidth(170); ground->setHeight(170);
	RenderComponent* rc = new RenderFrameComponent();
	ground->addRenderComponent(rc);
	stage.push_back(ground);

	GameComponent* ground2 = new GameComponent();
	ground2->setTextureId("27");
	Vector2D pos2(3.1, 1.7);
	ground2->setPosition(pos2);
	ground2->setWidth(170); ground2->setHeight(170);
	RenderComponent* rc2 = new RenderFrameComponent();
	ground2->addRenderComponent(rc2);
	stage.push_back(ground2);
}

void BattleState::pickArmors() {
	unsigned int i = 0;
	foundWP1 = false;
	foundWP2 = false;
	bool first = false;

	vector<estado> items = GameManager::Instance()->copyInventory();
	estado w1;
	estado w2;
	while (i < items.size() && !foundWP2) {

		if (items[i].equiped) {
			if (!first) {
				w1 = items[i];
				first = true;
				foundWP1 = true;
				W1id = w1.ID;
			}
			else {
				w2 = items[i];
				foundWP2 = true;
				W2id = w2.ID;
			}
		}
		i++;
	}

	Vector2D posWe(1, 1);

	if (foundWP1) {
		double scale = 2.5;

		double w = interfaz.button_0->getWidth() / scale;
		double h = interfaz.button_0->getHeight() / scale;

		positionW1.setX(interfaz.button_0->getPosition().getX() * scale);
		positionW1.setY(interfaz.button_0->getPosition().getY() * scale);

		positionW11.setX(interfaz.button_2->getPosition().getX() * scale);
		positionW11.setY(interfaz.button_2->getPosition().getY() * scale);

		string text1 = w1.tx;
		string name1 = w1.nombre;
		int colF1 = w1.colFrame;
		int rowF1 = w1.FilFrame;

		Weapon1 = new GameComponent();
		Weapon1->addRenderComponent(new RenderSingleFrameComponent());
		Weapon1->setTextureId(text1);
		Weapon1->setColFrame(colF1);
		Weapon1->setRowFrame(rowF1);
		Weapon1->setWidth(w); Weapon1->setHeight(h);
		Weapon1->setPosition(positionW1);
		Weapon1->setActive(false);
		stage.push_back(Weapon1);

		player->addAttack(ataques[W1id * 2]);

		Weapon11 = new GameComponent();
		Weapon11->addRenderComponent(new RenderSingleFrameComponent());
		Weapon11->setTextureId(text1);
		Weapon11->setColFrame(colF1);
		Weapon11->setRowFrame(rowF1);
		Weapon11->setWidth(w); Weapon11->setHeight(h);
		Weapon11->setPosition(positionW11);
		Weapon11->setActive(false);
		stage.push_back(Weapon11);

		player->addAttack(ataques[(W1id * 2) + 1]);
	}

	if (foundWP2) {
		double scale = 2.5;

		string text2 = w2.tx;
		string name2 = w2.nombre;
		int colF2 = w2.colFrame;
		int rowF2 = w2.FilFrame;

		double w = interfaz.button_0->getWidth() / scale;
		double h = interfaz.button_0->getHeight() / scale;

		positionW2.setX(interfaz.button_1->getPosition().getX() * scale);
		positionW2.setY(interfaz.button_1->getPosition().getY() * scale);

		positionW22.setX(interfaz.button_3->getPosition().getX() * scale);
		positionW22.setY((interfaz.button_3->getPosition().getY() * scale) * 1.01);

		Weapon2 = new GameComponent();
		Weapon2->addRenderComponent(new RenderSingleFrameComponent());
		Weapon2->setTextureId(text2);
		Weapon2->setColFrame(colF2);
		Weapon2->setRowFrame(rowF2);
		Weapon2->setWidth(w); Weapon2->setHeight(h);
		Weapon2->setPosition(positionW2);
		Weapon2->setActive(false);
		stage.push_back(Weapon2);

		player->addAttack(ataques[W2id * 2]);

		Weapon22 = new GameComponent();
		Weapon22->addRenderComponent(new RenderSingleFrameComponent());
		Weapon22->setTextureId(text2);
		Weapon22->setColFrame(colF2);
		Weapon22->setRowFrame(rowF2);
		Weapon22->setWidth(w); Weapon22->setHeight(h);
		Weapon22->setPosition(positionW22);
		Weapon22->setActive(false);
		stage.push_back(Weapon22);

		player->addAttack(ataques[(W2id * 2) + 1]);
	}
}

//bloque 3 (construccion de los personajes del bs) ------------------------------------------------------------------------
void BattleState::constructC() {
	//creamos contenido
	createPlayer();
	createEnemy();
	createStatus();
	createAttacks();

	//iniciamos combate
	initC();
}

void BattleState::createPlayer() {
	player = new BattlePlayer("Tyler", Physical, GameManager::Instance()->getHealth(), 10, 10, 100, 10);
	player->setTextureId("tylerSS");
	Vector2D pos(0.85, 0.7);
	iniPos = pos;
	player->setPosition(pos);
	player->setWidth(128); player->setHeight(256);
	player->setRowFrame(0); player->setColFrame(0);
	RenderComponent* rc = new RenderFraemeComponent2();
	player->addRenderComponent(rc);
	stage.push_back(player);
}

void BattleState::createEnemy()
{
	int rnd = GameManager::Instance()->getEnemy();
	int lv = GameManager::Instance()->getLevel();

	switch (rnd)
	{
	case 0:
		enemy = new BattleEnemy("Arbol", Physical, 300, 10, 10, 100, 11);
		enemy->setTextureId("arbolSS");
		break;

	case 1:
		enemy = new BattleEnemy("Basura", Magical, 300, 10, 10, 100, 11);
		enemy->setTextureId("basura");
		break;

	case 2:
		enemy = new BattleEnemy("Bocata", Magical, 300, 10, 10, 100, 11);
		enemy->setTextureId("bocata");
		break;

	case 3:
		enemy = new BattleEnemy("Libro Mates", Magical, 300, 10, 10, 100, 11);
		enemy->setTextureId("libro1");
		break;

	case 4:
		enemy = new BattleEnemy("Escoba", Physical, 300, 10, 10, 100, 11);
		enemy->setTextureId("escoba");
		break;

	case 5:
		enemy = new BattleEnemy("Pelotas", Physical, 300, 10, 10, 100, 11);
		enemy->setTextureId("pelotas");
		break;

	case 6:
		enemy = new BattleEnemy("Libro Lengua", Magical, 300, 10, 10, 100, 11);
		enemy->setTextureId("libro2");
		break;

	case 7:
		enemy = new BattleEnemy("Taquilla", Magical, 300, 10, 10, 100, 11);
		enemy->setTextureId("taquilla");
		break;

	case 8:
		enemy = new BattleEnemy("Avion", Magical, 300, 10, 10, 100, 11);
		enemy->setTextureId("avion");
		break;

	case 9:
		enemy = new BattleEnemy("Globo", Magical, 300, 10, 10, 100, 11);
		enemy->setTextureId("globo");
		break;
	}

	if (lv != 0) {
		enemy->setHealth(100 + (50 * lv));
		enemy->setAttack(10 + (rand() % lv));
		enemy->setDefense(10 + (rand() % lv));
		enemy->setVelocity(10 + (rand() % lv));
	}

	Vector2D pos2(3.3, 0.62);
	enemy->setPosition(pos2);
	enemy->setWidth(160);
	enemy->setHeight(260);

	RenderComponent* rc2 = new RenderFraemeComponent2();
	enemy->addRenderComponent(rc2);

	stage.push_back(enemy);
}

void BattleState::createStatus()
{
	Vector2D pos(0, 0);

	//PLAYER
	atqPP = new GameComponent();
	pos.setX(1); pos.setY(3);
	atqPP->setTextureId("ATQ+");
	atqPP->setWidth(60); atqPP->setHeight((60));
	atqPP->setPosition(pos);
	atqPP->addRenderComponent(new RenderFrameComponent());
	atqPP->setActive(false);
	stage.push_back(atqPP);

	atqMP = new GameComponent();
	pos.setX(0.5); pos.setY(3);
	atqMP->setTextureId("ATQ-");
	atqMP->setWidth(60); atqMP->setHeight((60));
	atqMP->setPosition(pos);
	atqMP->addRenderComponent(new RenderFrameComponent());
	atqMP->setActive(false);
	stage.push_back(atqMP);

	defPP = new GameComponent();
	pos.setX(1); pos.setY(4);
	defPP->setTextureId("DEF+");
	defPP->setWidth(60); defPP->setHeight((60));
	defPP->setPosition(pos);
	defPP->addRenderComponent(new RenderFrameComponent());
	defPP->setActive(false);
	stage.push_back(defPP);

	defMP = new GameComponent();
	pos.setX(0.5); pos.setY(4);
	defMP->setTextureId("DEF-");
	defMP->setWidth(60); defMP->setHeight((60));
	defMP->setPosition(pos);
	defMP->addRenderComponent(new RenderFrameComponent());
	defMP->setActive(false);
	stage.push_back(defMP);

	prcPP = new GameComponent();
	pos.setX(1); pos.setY(5);
	prcPP->setTextureId("PRC+");
	prcPP->setWidth(60); prcPP->setHeight((60));
	prcPP->setPosition(pos);
	prcPP->addRenderComponent(new RenderFrameComponent());
	prcPP->setActive(false);
	stage.push_back(prcPP);

	prcMP = new GameComponent();
	pos.setX(0.5); pos.setY(5);
	prcMP->setTextureId("PRC-");
	prcMP->setWidth(60); prcMP->setHeight((60));
	prcMP->setPosition(pos);
	prcMP->addRenderComponent(new RenderFrameComponent());
	prcMP->setActive(false);
	stage.push_back(prcMP);

	//ENEMY
	atqPE = new GameComponent();
	pos.setX(11.5); pos.setY(3);
	atqPE->setTextureId("ATQ+");
	atqPE->setWidth(60); atqPE->setHeight((60));
	atqPE->setPosition(pos);
	atqPE->addRenderComponent(new RenderFrameComponent());
	atqPE->setActive(false);
	stage.push_back(atqPE);

	atqME = new GameComponent();
	pos.setX(12); pos.setY(3);
	atqME->setTextureId("ATQ-");
	atqME->setWidth(60); atqME->setHeight((60));
	atqME->setPosition(pos);
	atqME->addRenderComponent(new RenderFrameComponent());
	atqME->setActive(false);
	stage.push_back(atqME);

	defPE = new GameComponent();
	pos.setX(11.5); pos.setY(4);
	defPE->setTextureId("DEF+");
	defPE->setWidth(60); defPE->setHeight((60));
	defPE->setPosition(pos);
	defPE->addRenderComponent(new RenderFrameComponent());
	defPE->setActive(false);
	stage.push_back(defPE);

	defME = new GameComponent();
	pos.setX(12); pos.setY(4);
	defME->setTextureId("DEF-");
	defME->setWidth(60); defME->setHeight((60));
	defME->setPosition(pos);
	defME->addRenderComponent(new RenderFrameComponent());
	defME->setActive(false);
	stage.push_back(defME);

	prcPE = new GameComponent();
	pos.setX(11.5); pos.setY(5);
	prcPE->setTextureId("PRC+");
	prcPE->setWidth(60); prcPE->setHeight((60));
	prcPE->setPosition(pos);
	prcPE->addRenderComponent(new RenderFrameComponent());
	prcPE->setActive(false);
	stage.push_back(prcPE);

	prcME = new GameComponent();
	pos.setX(12); pos.setY(5);
	prcME->setTextureId("PRC-");
	prcME->setWidth(60); prcME->setHeight((60));
	prcME->setPosition(pos);
	prcME->addRenderComponent(new RenderFrameComponent());
	prcME->setActive(false);
	stage.push_back(prcME);
}

void BattleState::createAttacks() {
	ataques.resize(33);
	// Ataques de Armas Fisicas
	//compas
	ataques[0] = Attack("360 No Scope", Physical, 20, 20, 65, 70, 1, 1, 0.8f);
	ataques[1] = Attack("¡Pasalo a Radianes!", Physical, 15, 15, 55, 85, 0.9f, 0.9f, 0.9f);
	//escobilla
	ataques[2] = Attack("Eso No Es\nChocolate", Physical, 15, 15, 40, 75, 0.9f, 1, 0.9f);
	ataques[3] = Attack("Limpieza a Fondo", Physical, 15, 15, 35, 80, 0.9f, 0.9f, 1);
	//menstruacion
	ataques[4] = Attack("Tajo Recto", Physical, 10, 10, 95, 80, 1, 1, 1);
	ataques[5] = Attack("Golpe de Remo", Physical, 15, 15, 80, 90, 1, 1, 1);
	//lapiz
	ataques[6] = Attack("Punta Afilada", Physical, 20, 20, 15, 75, 1, 1, 1);
	ataques[7] = Attack("Golpe de Goma", Physical, 20, 20, 20, 80, 1, 0.8f, 1);

	// Ataques de Armas Magicas
	//insulto
	ataques[8] = Attack("Hijo de Fruta", Magical, 20, 20, 20, 75, 0.9f, 0.9f, 1);
	ataques[9] = Attack("Dedo Mágico", Magical, 20, 20, 15, 80, 1, 1, 0.8f);
	//libro
	ataques[10] = Attack("Indice Confuso", Magical, 10, 10, 85, 95, 1, 1, 1);
	ataques[11] = Attack("Lectura Ligera", Magical, 10, 10, 95, 80, 1, 1, 1);
	//pegamento
	ataques[12] = Attack("Esto No Pega", Magical, 15, 15, 60, 90, 1, 0.9f, 1);
	ataques[13] = Attack("Metamaterial", Magical, 15, 15, 75, 80, 0.9f, 0.9f, 0.9f);

	//tartera
	ataques[14] = Attack("Comida Sorpresa", Magical, 20, 20, 30, 80, 1, 0.8f, 1);
	ataques[15] = Attack("Hoy Toca Lentejas", Magical, 20, 20, 45, 75, 1, 1, 1);

	// Ataques de Armas con Proyectiles
	//cerbatana
	ataques[16] = Attack("Proyectil Humedo", Ranged, 30, 30, 15, 90, 1, 1, 0.8f);
	ataques[17] = Attack("Escupitajo Supersonico", Ranged, 30, 30, 25, 80, 1, 1, 0.9f);
	//globo
	ataques[18] = Attack("Eso no era Agua", Ranged, 15, 15, 65, 85, 1, 1, 0.8f);
	ataques[19] = Attack("Eso Tampoco", Ranged, 15, 15, 75, 75, 1, 0.8f, 0.9f);
	//tirachinas
	ataques[20] = Attack("¡ZAS! En Toda la Boca", Ranged, 5, 5, 85, 100, 1, 1, 1);
	ataques[21] = Attack("Meteorito Hentai", Ranged, 5, 5, 95, 90, 1, 1, 1);
	//grapadora
	ataques[22] = Attack("Grapas Atómicas", Ranged, 25, 25, 30, 90, 1, 1, 1);
	ataques[23] = Attack("Corchograpa", Ranged, 25, 25, 45, 75, 1, 0.9f, 0.9f);

	// Ataques de Armas de Apoyo
	//sacapuntas
	ataques[24] = Attack("Afilador", Support, 20, 20, 0, 100, 1.2f, 1, 1);
	ataques[25] = Attack("Trazado Fino", Support, 20, 20, 100, 70, 1, 1, 1.2f);
	//calculadora
	ataques[26] = Attack("Calculo Algebraico Complejo", Support, 20, 20, 0, 100, 1.2f, 1, 1.1f);
	ataques[27] = Attack("Stack Overflow", Support, 5, 5, 0, 100, 1.5f, 1, 1);
	//bandeja
	ataques[28] = Attack("Reflejo Fidedigno", Support, 10, 10, 0, 100, 1, 1, 1.5f);
	ataques[29] = Attack("Escudo de Adamantium", Support, 5, 5, 0, 100, 1, 1.5f, 1);
	//borrador
	ataques[30] = Attack("Polvos de Tiza", Support, 20, 20, 0, 100, 1, 1.2f, 2);
	ataques[31] = Attack("Empezamos Tema Nuevo", Support, 5, 5, 0, 100, 1.4f, 1, 1.1f);

	//genericone
	ataques[32] = Attack("Sin Arma", Physical, 5, 5, 10, 100, 1, 1, 1);

	e_ataques.resize(12);
	e_ataques[0] = Attack("Placaje", Physical, 20, 20, 20, 90, 1, 1, 1);
	e_ataques[1] = Attack("Finta Lateral", Physical, 15, 15, 15, 80, 1, 1, 0.9f);
	e_ataques[2] = Attack("Golpe Bajo", Physical, 10, 10, 15, 30, 1, 0.8f, 1);
	e_ataques[3] = Attack("Aturdir", Physical, 15, 15, 35, 25, 0.9f, 1, 1);

	e_ataques[4] = Attack("Soplo", Ranged, 20, 20, 30, 90, 1, 0.9f, 1);
	e_ataques[5] = Attack("Vendaval", Ranged, 10, 10, 45, 90, 1, 1, 1);
	e_ataques[6] = Attack("Caida Libre", Ranged, 10, 10, 60, 50, 1, 1, 1);
	e_ataques[7] = Attack("Polvareda", Ranged, 15, 15, 15, 90, 1, 1, 0.8f);

	e_ataques[8] = Attack("Conjuro", Magical, 15, 15, 70, 90, 0.8f, 1, 1);
	e_ataques[9] = Attack("Maldición", Magical, 10, 10, 80, 90, 1, 0.8f, 1);
	e_ataques[10] = Attack("As Oculto", Magical, 5, 5, 90, 90, 0.9f, 0.9f, 1);
	e_ataques[11] = Attack("Psicosis", Magical, 5, 5, 35, 90, 0.9f, 0.9f, 0.9f);
}

void BattleState::initC() {
	if (!foundWP1) {
		player->addAttack(ataques[GOLPE]);
		player->addAttack(ataques[GOLPE]);
	}
	if (!foundWP2) {
		player->addAttack(ataques[GOLPE]);
		player->addAttack(ataques[GOLPE]);
	}

	std::vector<bool> ea;
	for (unsigned int i = 0; i < e_ataques.size(); i++) ea.push_back(true);
	Type aux_type = enemy->getType();
	int count = 0;
	while (count < 2)
	{
		int rnd = rand() % e_ataques.size();
		if (e_ataques[rnd].type == aux_type && ea[rnd])
		{
			ea[rnd] = false;
			count++;
			enemy->addAttack(e_ataques[rnd]);
		}
	}

	float vel_player = player->getVelocity();
	float vel_enemy = enemy->getVelocity();

	std::cout << std::endl << enemy->getName() << " quiere luchar!" << std::endl;
}

//bloque 4 (metodos del polimorfismo) -------------------------------------------------------------------------------------
void BattleState::update() {
	if (!fade2Done_ && fadeDone_)
		controlFade();
	else if (fade2Done_) {
		if (iniPos.getX() != player->getPosition().getX() && meleeAttack)
		{
			int frame = int(((SDL_GetTicks() / (75)) % 8)) + 4;
			player->setColFrame(frame);
		}
		else if (iniPos.getX() != player->getPosition().getX() && magicAttack)
		{
			int frame = int(((SDL_GetTicks() / (150)) % 15)) + 12;
			player->setColFrame(frame);
		}
		else if (iniPos.getX() != player->getPosition().getX() && rangedAttack)
		{
			int frame = int(((SDL_GetTicks() / (150)) % 9)) + 28;
			player->setColFrame(frame);
			if (frame >= 37)
				rangedAttack = false;
		}
		else {
			player->setColFrame(int(((SDL_GetTicks() / (200)) % 4)));
		}
		enemy->setColFrame(int(((SDL_GetTicks() / (400)) % 2)));
		GameState::update();
		if (!END_ && Attacking_) {
			END_ = run(); 
		}
		if (!damagedE || fail || crit || effect || notEffect || fai) contText++;
		else contText = 0;
		if (contText > 50) { 
			keepText = false; fail = false; damagedE = true; damagedP = true; crit = false; 
			effect = false; notEffect = false; fai = false;
			player->cancelCritical(); player->cancelEffective(); player->cancelNotEffective(); player->cancelFail();
		}
		else keepText = true;

		if (!damagedP || critE || effectE || notEffectE || faiE) contTextE++;
		else contTextE = 0;
		if (contTextE > 50) {
			keepTextE = false; damagedP = true; critE = false;
			effectE = false; notEffectE = false; faiE = false;
			enemy->cancelCritical(); enemy->cancelEffective(); enemy->cancelNotEffective(); enemy->cancelFail();
		}
		else keepTextE = true;

		//controlamos status
		controlStatus();
	}
	if (END_) {
		TheSoundManager::Instance()->stopMusic();
		TheSoundManager::Instance()->playMusic("music", 0);
	}
}

void BattleState::render() {
	if (!fadeDone_ && !fade2Done_) {
		stage[stage.size() - 1]->render();
		fadeDone_ = true;
	}
	else {
		GameState::render();
		updateVidas();

		if (weaponsEnabled_)
		{
			int posX = 420; int posX2 = 615;
			int posY = 485; int posY2 = 565;
			int posXpp = 480; int posXpp2 = 680;
			int posYpp = 445; int posYpp2 = 530;
			Attack temp_a;
			temp_a = player->getAttack(0);
			TheTextureManager::Instance()->drawText(temp_a.name, TextureManager::Pixel10, { 0,0,0,255 }, posX, posY, TheGame::Instance()->getRenderer());
			std::string temp_s = to_string(temp_a.pp) + "/" + to_string(temp_a.max_pp);
			TheTextureManager::Instance()->drawText(temp_s, TextureManager::Pixel16, { 0,0,0,255 }, posXpp, posYpp, TheGame::Instance()->getRenderer());
			temp_a = player->getAttack(1);
			TheTextureManager::Instance()->drawText(temp_a.name, TextureManager::Pixel10, { 0,0,0,255 }, posX, posY2, TheGame::Instance()->getRenderer());
			temp_s = to_string(temp_a.pp) + "/" + to_string(temp_a.max_pp);
			TheTextureManager::Instance()->drawText(temp_s, TextureManager::Pixel16, { 0,0,0,255 }, posXpp, posYpp2, TheGame::Instance()->getRenderer());
			temp_a = player->getAttack(2);
			TheTextureManager::Instance()->drawText(temp_a.name, TextureManager::Pixel10, { 0,0,0,255 }, posX2, posY, TheGame::Instance()->getRenderer());
			temp_s = to_string(temp_a.pp) + "/" + to_string(temp_a.max_pp);
			TheTextureManager::Instance()->drawText(temp_s, TextureManager::Pixel16, { 0,0,0,255 }, posXpp2, posYpp, TheGame::Instance()->getRenderer());
			temp_a = player->getAttack(3);
			TheTextureManager::Instance()->drawText(temp_a.name, TextureManager::Pixel10, { 0,0,0,255 }, posX2, posY2, TheGame::Instance()->getRenderer());
			temp_s = to_string(temp_a.pp) + "/" + to_string(temp_a.max_pp);
			TheTextureManager::Instance()->drawText(temp_s, TextureManager::Pixel16, { 0,0,0,255 }, posXpp2, posYpp2, TheGame::Instance()->getRenderer());
		}
		
		if ((!damagedE || fail) && keepText)
			TheTextureManager::Instance()->drawText("FALLO!", TextureManager::WapenFont50, { 255,0,0,255 }, 50, 175, TheGame::Instance()->getRenderer());

		if (player->isFail() && keepText) {
			TheTextureManager::Instance()->drawText("FALLO!", TextureManager::WapenFont50, { 255,0,0,255 }, 50, 175, TheGame::Instance()->getRenderer());
			fai = true;
		}

		if (player->isCritical() && keepText) {
			TheTextureManager::Instance()->drawText("CRITICO!", TextureManager::WapenFont50, { 255,0,0,255 }, 50, 175, TheGame::Instance()->getRenderer());
			crit = true;
		}
		if (player->isEffective() && keepText) {
			TheTextureManager::Instance()->drawText("MUY EFECTIVO!", TextureManager::WapenFont50, { 255,0,0,255 }, 50, 225, TheGame::Instance()->getRenderer());
			effect = true;
		}
		if (player->isNotEffective() && keepText) {
			TheTextureManager::Instance()->drawText("POCO EFECTIVO!", TextureManager::WapenFont50, { 255,0,0,255 }, 50, 225, TheGame::Instance()->getRenderer());
			notEffect = true;
		}

		if (enemy->isFail() && keepText) {
			TheTextureManager::Instance()->drawText("FALLO!", TextureManager::WapenFont50, { 255,0,0,255 }, 500, 175, TheGame::Instance()->getRenderer());
			faiE = true;
		}

		if (enemy->isCritical() && keepText) {
			TheTextureManager::Instance()->drawText("CRITICO!", TextureManager::WapenFont50, { 255,0,0,255 }, 500, 175, TheGame::Instance()->getRenderer());
			critE = true;
		}
		if (enemy->isEffective() && keepText) {
			TheTextureManager::Instance()->drawText("MUY EFECTIVO!", TextureManager::WapenFont50, { 255,0,0,255 }, 450, 225, TheGame::Instance()->getRenderer());
			effectE = true;
		}
		if (enemy->isNotEffective() && keepText) {
			TheTextureManager::Instance()->drawText("POCO EFECTIVO!", TextureManager::WapenFont50, { 255,0,0,255 }, 450, 225, TheGame::Instance()->getRenderer());
			notEffectE = true;
		}
	}
}

bool BattleState::handleEvent(const SDL_Event& event) {
	bool handledEvent = false;
	bool actButton = false;

	if (fade2Done_) {
		handledEvent = GameState::handleEvent(event);

		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_RETURN) {
				if (enemy->getTurn()) {
					okEnemy_ = true;
				}
				else if (!enemy->getTurn() && !attackAnim_) {
					okPlayer_ = true;
					okEnemy_ = false;
					interfaz.pruebaTexto_->setTextureId("selOptTexto");
				}

				if (END_)
					Game::Instance()->getStateMachine()->popState();

				handledEvent = true;
			}
		}

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (enemy->getTurn()) {
				okEnemy_ = true;
			}
			else if (!enemy->getTurn() && !attackAnim_) {
				okPlayer_ = true;
				okEnemy_ = false;
				interfaz.pruebaTexto_->setTextureId("selOptTexto");
			}

			if (END_) {
				GameManager::Instance()->exitBattle();
				Game::Instance()->getStateMachine()->popState();
			}

			handledEvent = true;
		}

		if (!attackAnim_ && okPlayer_)
			actButton = interfaz.button_0->handleEvent(event);
		else
			actButton = false;

		if (actButton && !attack_) {
			in = true;
			toAttackMode();
		}
		else if (actButton && attack_) {
			attack(0);
			disableWapons();
		}

		if (!attackAnim_ && okPlayer_)
			actButton = interfaz.button_1->handleEvent(event);
		else
			actButton = false;

		if (actButton && !attack_) {
			potion = true;
			attack(-1);
		}
		else if (actButton && attack_) {
			attack(2);
			disableWapons();
		}

		if (!attackAnim_ && okPlayer_)
			actButton = interfaz.button_2->handleEvent(event);
		else
			actButton = false;

		if (actButton && !attack_) {
			in = true;
			toAttackMode();
		}
		else if (actButton && attack_) {
			attack(1);
			disableWapons();
		}

		if (!attackAnim_ && okPlayer_)
			actButton = interfaz.button_3->handleEvent(event);
		else
			actButton = false;

		if (actButton && !attack_) {
			in = true;
			run_ = true;
			TheSoundManager::Instance()->stopMusic();
			TheSoundManager::Instance()->playMusic("music", 0);
			Game::Instance()->getStateMachine()->popState();
		}
		else if (actButton && attack_) {
			attack(3);
			disableWapons();
		}
	}

	return handledEvent || actButton;
}

//bloque 5 (auxiliares de update) -----------------------------------------------------------------------------------------
void BattleState::controlFade() {
	if (alpha_ > 0) {
		SDL_SetTextureAlphaMod(TheTextureManager::Instance()->getTexture("23"), alpha_);
		alpha_ = alpha_ - 20;
	}
	else {
		GameObject* aux = stage.back();
		if (aux != 0) delete aux;
		stage.pop_back();
		fade2Done_ = true;
	}
}

bool BattleState::run()
{
	if (lastTurn)
		return true;

	else if ((GameManager::Instance()->getHealth() > 0 && enemy->getHealth() > 0) || !lastTurn)
	{
		bool pt = player->getTurn();
		bool et = enemy->getTurn();

		if (pt && !et) {
			std::cout << std::endl;

			if (input != -1 && !player->useAttack(input)) {
				std::cout << "No quedan PP para este ataque!" << std::endl;
				fail = true;
			}
			else {
				fail = false;
				float dmg;
				if (input != -1)
					dmg = player->combat(input, enemy->getDefense(), enemy->getType(), damagedE);
				else
					dmg = 0;

				if (player->hasTarget())
				{
					enemy->receiveDamage(dmg);
					Attack temp_a;
					if (input != -1)
						temp_a = player->getAttack(input);
					else
						temp_a = Attack("Pocion", Support, 100, 100, 0, 1000, 1, 1, 1);

					if (temp_a.type != Support)
						enemy->receiveFactors(temp_a.atk_factor, temp_a.def_factor, temp_a.prc_factor);
				}
			}
			std::cout << std::endl;
			enemy->setTurn(true);
		}

		if (enemy->getHealth() > 0 && !pt && et && okEnemy_)
		{
			interfaz.pruebaTexto_->setTextureId("enemAtacoTexto");
			enemy->useAttack(0);
			int e_input = enemy->getInput();

			float dmg = enemy->combat(e_input, player->getDefense(), player->getType(), damagedP);

			enemy->delPhysicsComponent(&mce);
			enemy->delPhysicsComponent(&mae);
			Attack a = enemy->getAttack(e_input);

			if ((a.type == Physical)) {
				Vector2D p = player->getPosition();
				Vector2D e = enemy->getPosition();
				mce = MoveToThisPosComponent(e, p);
				enemy->addPhysicsComponent(&mce);
				attackAnim_ = true;
			}
			else if (a.type == Ranged) {
				Vector2D p = player->getPosition();
				Vector2D e = enemy->getPosition();
				Vector2D x(0, 0);
				float px = e.getX() + 1;
				x.setX(px);
				mce = MoveToThisPosComponent(e, x);
				enemy->addPhysicsComponent(&mce);
				attackAnim_ = true;
			}
			else if ((a.type == Magical || a.type == Support)) {
				Vector2D e = enemy->getPosition();
				mae = MagicAttackComponent(e, 0.3);
				enemy->addPhysicsComponent(&mae);
				attackAnim_ = true;
			}

			if (enemy->hasTarget())
			{
				player->receiveDamage(dmg);
				Attack temp_a = enemy->getAttack(e_input);
				if (temp_a.type != Support)
					player->receiveFactors(temp_a.atk_factor, temp_a.def_factor, temp_a.prc_factor);
			}

			enemy->setTurn(false);
		}

		if (!pt && !et && Attacking_) {
			std::cout << player->getName() << ": " << GameManager::Instance()->getHealth() << " HP" << std::endl;
			std::cout << enemy->getName() << ": " << enemy->getHealth() << " HP" << std::endl;

			std::cout << std::endl << "-------------------------------------------------------------" << std::endl;

			Attacking_ = false;
		}
	}

	if (GameManager::Instance()->getHealth() > 0 && enemy->getHealth() <= 0) {
		std::cout << "HAS GANADO!" << std::endl;
		lastTurn = true;
	}
	else if (GameManager::Instance()->getHealth() <= 0 && enemy->getHealth() > 0) {
		std::cout << "HAS PERDIDO!" << std::endl;
		lastTurn = true;
	}
	else if (GameManager::Instance()->getHealth() <= 0 && enemy->getHealth() <= 0) {
		std::cout << "WTF EMPATE LOCO!" << std::endl;
		lastTurn = true;
	}
	return false;
}

void BattleState::controlStatus() {
	//player attack
	if (player->getAtkFactor() > 1) {
		atqPP->setActive(true);
		atqMP->setActive(false);
	}
	else if (player->getAtkFactor() < 1) {
		atqMP->setActive(true);
		atqPP->setActive(false);
	}
	else {
		atqPP->setActive(false);
		atqMP->setActive(false);
	}
	//player defense
	if (player->getDefFactor() > 1) {
		defPP->setActive(true);
		defMP->setActive(false);
	}
	else if (player->getDefFactor() < 1) {
		defMP->setActive(true);
		defPP->setActive(false);
	}
	else {
		defPP->setActive(false);
		defMP->setActive(false);
	}
	//player precition
	if (player->getPrcFactor() > 1) {
		prcPP->setActive(true);
		prcMP->setActive(false);
	}
	else if (player->getPrcFactor() < 1) {
		prcMP->setActive(true);
		prcPP->setActive(false);
	}
	else {
		prcPP->setActive(false);
		prcMP->setActive(false);
	}

	//enemy attack
	if (enemy->getAtkFactor() > 1) {
		atqPE->setActive(true);
		atqME->setActive(false);
	}
	else if (enemy->getAtkFactor() < 1) {
		atqME->setActive(true);
		atqPE->setActive(false);
	}
	else {
		atqPE->setActive(false);
		atqME->setActive(false);
	}
	//enemy defense
	if (enemy->getDefFactor() > 1) {
		defPE->setActive(true);
		defME->setActive(false);
	}
	else if (enemy->getDefFactor() < 1) {
		defME->setActive(true);
		defPE->setActive(false);
	}
	else {
		defPE->setActive(false);
		defME->setActive(false);
	}
	//enemy precition
	if (enemy->getPrcFactor() > 1) {
		prcPE->setActive(true);
		prcME->setActive(false);
	}
	else if (enemy->getPrcFactor() < 1) {
		prcME->setActive(true);
		prcPE->setActive(false);
	}
	else {
		prcPE->setActive(false);
		prcME->setActive(false);
	}
}

//bloque 6 (auxiliares de render) -----------------------------------------------------------------------------------------
void BattleState::updateVidas()
{
	Vector2D position0(102, 81);
	Vector2D position1(576, 81);

	int iniwidth = 120;
	int height = 8;

	int width = (GameManager::Instance()->getHealth() < GameManager::Instance()->getMaxHealth()) ? (GameManager::Instance()->getHealth() * iniwidth / GameManager::Instance()->getMaxHealth()) : iniwidth;
	if (width < 0) width = 0;

	SDL_Rect fillRect = { (int)position0.getX(), (int)position0.getY() , width, height };
	if (width > iniwidth / 2)
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
	else if (width > iniwidth / 3)
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0xFF, 0xFF, 0x00, 0xFF);
	else
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(Game::Instance()->getRenderer(), &fillRect);

	width = (enemy->getHealth() < enemy->getMaxHealth()) ? (enemy->getHealth() * iniwidth / enemy->getMaxHealth()) : iniwidth;
	if (width < 0) width = 0;

	SDL_Rect fillRect2 = { (Uint32)position1.getX(), (Uint32)position1.getY() , width, height };
	if (width > iniwidth / 2)
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
	else if (width > iniwidth / 3)
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0xFF, 0xFF, 0x00, 0xFF);
	else
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(Game::Instance()->getRenderer(), &fillRect2);
}

//bloque 7 (auxiliares de handle events) ----------------------------------------------------------------------------------
void BattleState::toAttackMode() {
	attack_ = true;
	displayAttacks();
	stage[1]->setTextureId("29");
	enableWapons();
}

void BattleState::displayAttacks()
{
	for (int i = 0; i < 4; i++) {
		Attack temp_a = player->getAttack(i);
		std::cout << temp_a.pp << "/" << temp_a.max_pp << " " << temp_a.name << " (" << temp_a.strength << ")" << std::endl;
	}


}

void BattleState::attack(int i) {
	player->setTurn(true);

	stage[1]->setTextureId("24");
	input = i;
	Attacking_ = true;
	attackAnim_ = true;
	attack_ = false; bag_ = false; run_ = false; okPlayer_ = false;

	Vector2D p = player->getPosition();
	Vector2D e = enemy->getPosition();

	Attack a;
	if (input != -1)
		a = player->getAttack(input);
	else
		a = Attack("Pocion", Support, 100, 100, 0, 1000, 1, 1, 1);

	player->delPhysicsComponent(&mcp);
	player->delPhysicsComponent(&map);

	if (input != -1) {
		if ((a.type == Physical)) {
			mcp = MoveToThisPosComponent(p, e);
			player->addPhysicsComponent(&mcp);
			meleeAttack = true;
			magicAttack = false;
			rangedAttack = false;
		}
		else if (a.type == Ranged) {
			Vector2D x(0, 0);
			float px = p.getX() - 1;
			x.setX(px);
			mcp = MoveToThisPosComponent(p, x, 0.05);
			player->addPhysicsComponent(&mcp);
			meleeAttack = false;
			magicAttack = false;
			rangedAttack = true;
		}
		else if ((a.type == Magical || a.type == Support)) {
			map = MagicAttackComponent(p, 0.3);
			player->addPhysicsComponent(&map);
			meleeAttack = false;
			magicAttack = true;
			rangedAttack = false;
		}
	}
	else {
		if (potion) {
			potion = false;
			map = MagicAttackComponent(p, 0.3);
			player->addPhysicsComponent(&map);
			meleeAttack = false;
			magicAttack = true;
			rangedAttack = false;

			int potions = GameManager::Instance()->getPotions();
			if (potions > 0) {
				potions--;
				GameManager::Instance()->setPotions(potions);
				GameManager::Instance()->setHealth(GameManager::Instance()->getHealth() + 50);
			}
		}
	}

	//texto
	interfaz.pruebaTexto_->setTextureId("jugAtacoTexto");

	//desactivas flag
	in = false;
}

void BattleState::enableWapons() {
	weaponsEnabled_ = true;
	if (foundWP1) {
		Weapon1->setActive(true);
		Weapon11->setActive(true);
	}
	if (foundWP2) {
		Weapon2->setActive(true);
		Weapon22->setActive(true);
	}
}

void BattleState::disableWapons() {
	weaponsEnabled_ = false;
	if (foundWP1) {
		Weapon1->setActive(false);
		Weapon11->setActive(false);
	}
	if (foundWP2) {
		Weapon2->setActive(false);
		Weapon22->setActive(false);
	}
}