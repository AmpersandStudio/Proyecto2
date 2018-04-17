#include "BattleState.h"
#include "TextureManager.h"
#include "RenderSingleFrameComponent.h"
#include "RenderFraemeComponent2.h"

BattleState::BattleState()
{
	//Texturas necesitadas
	//interfaz.cuadro_principal = Game::Instance()->getTexture(24);
	//interfaz.cuadro_personaje = Game::Instance()->getTexture(26);
	//interfaz.cuadro_enemigo = Game::Instance()->getTexture(25);
	//interfaz.cuadro_ataque = Game::Instance()->getTexture(29);
	//interfaz.Vida = Game::Instance()->getTexture(20);
	//interfaz.botones = Game::Instance()->getTexture(28);
	//interfaz.ground = Game::Instance()->getTexture(27);

	attack_ = false; bag_ = false; run_ = false;
	okEnemy_ = false; okPlayer_ = true;

	//JR para el inicio
	rcfade = new RenderFullComponent();
	alpha_ = 255;
	fade_ = new GameComponent();
	fade_->setTextureId("23");
	fade_->addRenderComponent(rcfade);
	fadeDone_ = false;
	fade2Done_ = false;

	END_ = false; Attacking_ = false; attackAnim_ = false;

	//Componentes necesarios

	fondo_ = new GameComponent();
	fondo_->setTextureId("fondoBatallaTuto");
	fondo_->addRenderComponent(new RenderFullComponent());

	createUI();

}

BattleState::~BattleState()
{
	SDL_SetTextureAlphaMod(TheTextureManager::Instance()->getTexture("23"), 255); //para restaurar el alpha original
	if (interfaz.button_0 != 0) delete interfaz.button_0;
	if (interfaz.button_1 != 0) delete interfaz.button_1;
	if (interfaz.button_2 != 0) delete interfaz.button_2;
	if (interfaz.button_3 != 0) delete interfaz.button_3;
}

void BattleState::init() {
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

void BattleState::createUI() {

	stage.clear();

	stage.push_back(fondo_);

	//Panel de fondo
	Vector2D position0(0, 2.55);
	GameComponent* UI_Background = new GameComponent();
	UI_Background->setTextureId("24");
	UI_Background->setWidth(Game::Instance()->getWinWidth()); UI_Background->setHeight((170));
	UI_Background->setPosition(position0);
	UI_Background->addRenderComponent(new RenderFrameComponent());
	stage.push_back(UI_Background);

	createBattleButtons();
	createCharacterInfo();
	

	/*GameComponent* UI_Text = new GameComponent(game);
	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
	SDL_Color Black = { 0, 0, 0 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Aquí van los mensajes de batalla", Black);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);*/

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

	//preparamos el combate
	constructC();

	int i = 0;
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

		int w = interfaz.button_0->getWidth();
		int h = interfaz.button_0->getHeight();

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
		posWe = interfaz.button_0->getPosition();
		Weapon1->setPosition(posWe);
		Weapon1->setActive(false);
		stage.push_back(Weapon1);

		player->addAttack(ataques[W1id*2]);

		Weapon11 = new GameComponent();
		Weapon11->addRenderComponent(new RenderSingleFrameComponent());
		Weapon11->setTextureId(text1);
		Weapon11->setColFrame(colF1);
		Weapon11->setRowFrame(rowF1);
		Weapon11->setWidth(w); Weapon11->setHeight(h);
		posWe = interfaz.button_2->getPosition();
		Weapon11->setPosition(posWe);
		Weapon11->setActive(false);
		stage.push_back(Weapon11);

		player->addAttack(ataques[(W1id * 2) + 1]);
	}

	if (foundWP2) {

		string text2 = w2.tx;
		string name2 = w2.nombre;
		int colF2 = w2.colFrame;
		int rowF2 = w2.FilFrame;

		int w = interfaz.button_0->getWidth();
		int h = interfaz.button_0->getHeight();

		Weapon2 = new GameComponent();
		Weapon2->addRenderComponent(new RenderSingleFrameComponent());
		Weapon2->setTextureId(text2);
		Weapon2->setColFrame(colF2);
		Weapon2->setRowFrame(rowF2);
		Weapon2->setWidth(w); Weapon2->setHeight(h);
		posWe = interfaz.button_1->getPosition();
		Weapon2->setPosition(posWe);
		Weapon2->setActive(false);
		stage.push_back(Weapon2);

		player->addAttack(ataques[W2id * 2]);

		Weapon22 = new GameComponent();
		Weapon22->addRenderComponent(new RenderSingleFrameComponent());
		Weapon22->setTextureId(text2);
		Weapon22->setColFrame(colF2);
		Weapon22->setRowFrame(rowF2);
		Weapon22->setWidth(w); Weapon22->setHeight(h);
		posWe = interfaz.button_3->getPosition();
		Weapon22->setPosition(posWe);
		Weapon22->setActive(false);
		stage.push_back(Weapon22);

		player->addAttack(ataques[(W2id * 2) + 1]);
	}
	//fade inicial
	stage.push_back(fade_);
}

void BattleState::constructC() {
	player = new BattlePlayer("Tyler", Physical, 1000, 10, 10, 100, 10);
	player->setTextureId("tylerSS");
	Vector2D pos(0.85, 0.7);
	iniPos = pos;
	player->setPosition(pos);
	player->setWidth(128); player->setHeight(256);
	player->setRowFrame(0); player->setColFrame(0);
	RenderComponent* rc = new RenderFraemeComponent2();
	player->addRenderComponent(rc);
	stage.push_back(player);

	enemy = new BattleEnemy("Pajaro", Ranged, 70, 10, 10, 100, 11);
	enemy->setTextureId("arbolSS");
	Vector2D pos2(3.3, 0.62);
	enemy->setPosition(pos2);
	enemy->setWidth(160); enemy->setHeight(260);
	RenderComponent* rc2 = new RenderFraemeComponent2();
	enemy->addRenderComponent(rc2);
	stage.push_back(enemy);

	ataques.resize(33);

	// Ataques de Armas Fisicas
	//compas
	ataques[0] = Attack("360 No Scope", Physical, 20, 20, 65, 70, 1, 1, 0.8f);
	ataques[1] = Attack("¡Pasalo a Radianes!", Physical, 15, 15, 55, 85, 0.9f, 0.9f, 0.9f);
	//escobilla
	ataques[2] = Attack("Eso No Es Chocolate", Physical, 15, 15, 40, 75, 0.9f, 1, 0.9f);
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
	ataques[25] = Attack("Trazado Fino", Support, 20, 0, 100, 20, 1, 1, 1.2f);
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
	ataques[32] = Attack("Golpe", Physical, 5, 5, 10, 100, 1.4f, 1, 1.1f);

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

	initC();
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
	for (int i = 0; i < e_ataques.size(); i++) ea.push_back(true);
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
	// TODO
	// Definir quién empieza

	std::cout << std::endl << enemy->getName() << " quiere luchar!" << std::endl;
}

void BattleState::displayAttacks()
{
	for (int i = 0; i < 4; i++) {
		Attack temp_a = player->getAttack(i);
		std::cout << temp_a.pp << "/" << temp_a.max_pp << " " << temp_a.name << " (" << temp_a.strength << ")" << std::endl;
	}
}

void BattleState::handleInput()
{
	displayAttacks();
	input = 0;
	do {
		std::cout << "Que quieres hacer? ";
		std::cin >> input;
	} while (input < 1 || input > 4);

	std::cout << std::endl;

	input--;
}

bool BattleState::run()
{
	if (lastTurn)
		return true;

	else if ((player->getHealth() > 0 && enemy->getHealth() > 0) || !lastTurn)
	{
		bool pt = player->getTurn();
		bool et = enemy->getTurn();

		if (pt && !et) {
			std::cout << std::endl;

			//handleInput();
			if (!player->useAttack(input)) {
				std::cout << "No quedan PP para este ataque!" << std::endl;
			}
			else {

				float dmg = player->combat(input, enemy->getDefense(), enemy->getType());
				if (player->hasTarget())
				{
					enemy->receiveDamage(dmg);
					Attack temp_a = player->getAttack(input);
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
			float dmg = enemy->combat(e_input, player->getDefense(), player->getType());

			enemy->delPhysicsComponent(mc);
			Vector2D p = player->getPosition();
			Vector2D e = enemy->getPosition();
			mc = new MoveToThisPosComponent(e, p);
			enemy->addPhysicsComponent(mc);
			attackAnim_ = true;

			if (enemy->hasTarget())
			{
				player->receiveDamage(dmg);
				Attack temp_a = enemy->getAttack(e_input);
				player->receiveFactors(temp_a.atk_factor, temp_a.def_factor, temp_a.prc_factor);
			}
			enemy->setTurn(false);
		}

		if (!pt && !et && Attacking_) {
			std::cout << player->getName() << ": " << player->getHealth() << " HP" << std::endl;
			std::cout << enemy->getName() << ": " << enemy->getHealth() << " HP" << std::endl;

			std::cout << std::endl << "-------------------------------------------------------------" << std::endl;

			Attacking_ = false;
		}
	}

	if (player->getHealth() > 0 && enemy->getHealth() <= 0) {
		std::cout << "HAS GANADO!" << std::endl;
		lastTurn = true;
	}
	else if (player->getHealth() <= 0 && enemy->getHealth() > 0) {
		std::cout << "HAS PERDIDO!" << std::endl;
		lastTurn = true;
	}
	else if (player->getHealth() <= 0 && enemy->getHealth() <= 0) {
		std::cout << "WTF EMPATE LOCO!" << std::endl;
		lastTurn = true;
	}
	return false;
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
	position0.setX(2.4); position0.setY(7.5);
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

	//Boton Testeo Barra Vida
	/*Button* test = new Button(game, reduceVida, 4);
	position0.setX(2); position0.setY(4.4);
	test->setText(interfaz.botones); test->setPosition(position0); test->setWidth(buttonWidth); test->setHeight(buttonHeight);
	test->addRenderComponent(rcF); test->addInputComponent(MIC);
	stage.push_back(test);*/
}

void BattleState::updateVidas()
{
	Vector2D position0(102, 81);
	Vector2D position1(576, 81);

	int iniwidth = 120;
	int height = 8;

	int width = (player->getHealth() < player->getMaxHealth()) ? (player->getHealth() * iniwidth / player->getMaxHealth()) : iniwidth;
	if (width < 0) width = 0;

	SDL_Rect fillRect = { (Uint32)position0.getX(), (Uint32)position0.getY() , width, height};
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

void BattleState::updateVida(GameComponent* barraVida, double variacion)
{
	barraVida->setWidth(barraVida->getWidth()*variacion);
	Vector2D positionNew(barraVida->getPosition().getX() * (1 / variacion), barraVida->getPosition().getY());
	stage.push_back(barraVida);
}

bool BattleState::isButton(GameObject * object)
{
	if (typeid(object) == typeid(Button())) {
		return true;
	}
	return false;
}

void BattleState::update() {

	if (TheSoundManager::Instance()->isPlayingMusic() == 0) {
		TheSoundManager::Instance()->playMusic("loop_btl", 100);
		TheSoundManager::Instance()->setMusicVolume(MIX_MAX_VOLUME / 2);
	}

	if (!fade2Done_ && fadeDone_)
		init();
	else if (fade2Done_) {
		if (iniPos.getX() != player->getPosition().getX())
		{
			int frame = int(((SDL_GetTicks() / (75)) % 8)) + 4;
			player->setColFrame(frame);
		}
		else {
			player->setColFrame(int(((SDL_GetTicks() / (200)) % 4)));
		}
		enemy->setColFrame(int(((SDL_GetTicks() / (400)) % 2)));
		GameState::update();
		if (!END_ && Attacking_) {
			END_ = run();
		}
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

			if (END_)
				Game::Instance()->getStateMachine()->popState();

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
			in = true;
			bag_ = true;
			in = false; //habra que desactivarla en algun punto
		}
		else if (actButton && attack_) {
			attack(1);
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
			attack(2);
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

void BattleState::attack(int i) {
	player->setTurn(true);

	//antes de nada le quitamos el comp
	player->delPhysicsComponent(mc);

	stage[1]->setTextureId("24");
	input = i;
	Attacking_ = true;
	attackAnim_ = true;
	attack_ = false; bag_ = false; run_ = false; okPlayer_ = false;

	Vector2D p = player->getPosition();
	Vector2D e = enemy->getPosition();
	mc = new MoveToThisPosComponent(p, e);
	player->addPhysicsComponent(mc);

	//texto
	interfaz.pruebaTexto_->setTextureId("jugAtacoTexto");

	//desactivas flag
	in = false;
}

void BattleState::toAttackMode() {
	attack_ = true;
	displayAttacks();
	stage[1]->setTextureId("29");
	enableWapons();
}