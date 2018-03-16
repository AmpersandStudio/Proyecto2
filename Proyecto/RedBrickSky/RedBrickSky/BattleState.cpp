#include "BattleState.h"
#include "TextureManager.h"

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

	//JR para el inicio
	rcfade = new RenderFullComponent();
	alpha_ = 255;
	fade_ = new GameComponent();
	fade_->setTextureId("23");
	fade_->addRenderComponent(rcfade);
	fadeDone_ = false;
	fade2Done_ = false;

	END_ = false; Attacking_ = false;

	//Componentes necesarios
	rcF = new RenderFrameComponent(); //Render Frame
	rc = new RenderFullComponent(); //Render FS
									//Info = new MouseInfoClickComponent();
	MIC = new MouseInputForBattleComponent();

	fondo_ = new GameComponent();
	fondo_->setTextureId("fondoBatallaTuto");
	fondo_->addRenderComponent(new RenderFullComponent());

	createUI();

}

BattleState::~BattleState()
{
	SDL_SetTextureAlphaMod(TheTextureManager::Instance()->getTexture("23"), 255); //para restaurar el alpha original
}

void BattleState::init() {
	if (alpha_ > 0) {
		SDL_SetTextureAlphaMod(TheTextureManager::Instance()->getTexture("23"), alpha_);
		alpha_ = alpha_ - 20;
	}
	else {
		stage.pop_back();
		fade2Done_ = true;
	}
}

void BattleState::createUI() {

	stage.clear();

	stage.push_back(fondo_);

	//Panel de fondo
	Vector2D position0(0, 2.6);
	GameComponent* UI_Background = new GameComponent();
	UI_Background->setTextureId("24");
	UI_Background->setWidth(Game::Instance()->getWinWidth()); UI_Background->setHeight((200));
	UI_Background->setPosition(position0);
	UI_Background->addRenderComponent(rcF);
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
	Vector2D pos(0.8, 1.7);
	ground->setPosition(pos);
	ground->setWidth(200); ground->setHeight(200);
	RenderComponent* rc = new RenderFrameComponent();
	ground->addRenderComponent(rc);
	stage.push_back(ground);

	GameComponent* ground2 = new GameComponent();
	ground2->setTextureId("27");
	Vector2D pos2(4.625, 1.7);
	ground2->setPosition(pos2);
	ground2->setWidth(200); ground2->setHeight(200);
	RenderComponent* rc2 = new RenderFrameComponent();
	ground2->addRenderComponent(rc2);
	stage.push_back(ground2);

	//preparamos el combate
	constructC();

	//fade inicial
	stage.push_back(fade_);

	Vector2D p = player->getPosition();
	Vector2D e = enemy->getPosition();
	mc = new MoveToThisPosComponent(p, e);
}

void BattleState::constructC() {
	player = new BattlePlayer("Tyler", Physical, 100, 10, 10, 100, 10);
	player->setTextureId("BattlePlayer");
	Vector2D pos(0.88, 1.42);
	player->setPosition(pos);
	player->setWidth(200); player->setHeight(200);
	RenderComponent* rc = new RenderFrameComponent();
	player->addRenderComponent(rc);
	stage.push_back(player);

	enemy = new BattleEnemy("Pajaro", Ranged, 70, 10, 10, 100, 11);
	enemy->setTextureId("BattleEnemy");
	Vector2D pos2(4.625, 1.5);
	enemy->setPosition(pos2);
	enemy->setWidth(200); enemy->setHeight(200);
	RenderComponent* rc2 = new RenderFrameComponent();
	enemy->addRenderComponent(rc2);
	stage.push_back(enemy);

	ataques.resize(32);

	// Ataques de Armas Fisicas
	ataques[0] = Attack("Punta Afilada", Physical, 20, 20, 15, 75, 1, 1, 1);
	ataques[1] = Attack("Golpe de Goma", Physical, 20, 20, 20, 80, 1, 0.8f, 1);
	ataques[2] = Attack("Eso No Es Chocolate", Physical, 15, 15, 40, 75, 0.9f, 1, 0.9f);
	ataques[3] = Attack("Limpieza a Fondo", Physical, 15, 15, 35, 80, 0.9f, 0.9f, 1);
	ataques[4] = Attack("360 No Scope", Physical, 20, 20, 65, 70, 1, 1, 0.8f);
	ataques[5] = Attack("¡Pasalo a Radianes!", Physical, 15, 15, 55, 85, 0.9f, 0.9f, 0.9f);
	ataques[6] = Attack("Tajo Recto", Physical, 10, 10, 95, 80, 1, 1, 1);
	ataques[7] = Attack("Golpe de Remo", Physical, 15, 15, 80, 90, 1, 1, 1);

	// Ataques de Armas Magicas
	ataques[8] = Attack("Hijo de Fruta", Magical, 20, 20, 20, 75, 0.9f, 0.9f, 1);
	ataques[9] = Attack("Dedo Mágico", Magical, 20, 20, 15, 80, 1, 1, 0.8f);
	ataques[10] = Attack("Comida Sorpresa", Magical, 20, 20, 30, 80, 1, 0.8f, 1);
	ataques[11] = Attack("Hoy Toca Lentejas", Magical, 20, 20, 45, 75, 1, 1, 1);
	ataques[12] = Attack("Esto No Pega", Magical, 15, 15, 60, 90, 1, 0.9f, 1);
	ataques[13] = Attack("Metamaterial", Magical, 15, 15, 75, 80, 0.9f, 0.9f, 0.9f);
	ataques[14] = Attack("Indice Confuso", Magical, 10, 10, 85, 95, 1, 1, 1);
	ataques[15] = Attack("Lectura Ligera", Magical, 10, 10, 95, 80, 1, 1, 1);

	// Ataques de Armas con Proyectiles
	ataques[16] = Attack("Proyectil Humedo", Ranged, 30, 30, 15, 90, 1, 1, 0.8f);
	ataques[17] = Attack("Escupitajo Supersonico", Ranged, 30, 30, 25, 80, 1, 1, 0.9f);
	ataques[22] = Attack("Grapas Atómicas", Ranged, 25, 25, 30, 90, 1, 1, 1);
	ataques[23] = Attack("Corchograpa", Ranged, 25, 25, 45, 75, 1, 0.9f, 0.9f);
	ataques[19] = Attack("Eso no era Agua", Ranged, 15, 15, 65, 85, 1, 1, 0.8f);
	ataques[18] = Attack("Eso Tampoco", Ranged, 15, 15, 75, 75, 1, 0.8f, 0.9f);
	ataques[20] = Attack("¡ZAS! En Toda la Boca", Ranged, 5, 5, 85, 100, 1, 1, 1);
	ataques[21] = Attack("Meteorito Hentai", Ranged, 5, 5, 95, 90, 1, 1, 1);

	// Ataques de Armas de Apoyo
	ataques[24] = Attack("Afilador", Support, 20, 20, 0, 100, 1.2f, 1, 1);
	ataques[25] = Attack("Trazado Fino", Support, 20, 0, 100, 20, 1, 1, 1.2f);
	ataques[26] = Attack("Calculo Algebraico Complejo", Support, 20, 20, 0, 100, 1.2f, 1, 1.1f);
	ataques[27] = Attack("Stack Overflow", Support, 5, 5, 0, 100, 1.5f, 1, 1);
	ataques[28] = Attack("Reflejo Fidedigno", Support, 10, 10, 0, 100, 1, 1, 1.5f);
	ataques[29] = Attack("Escudo de Adamantium", Support, 5, 5, 0, 100, 1, 1.5f, 1);
	ataques[30] = Attack("Polvos de Tiza", Support, 20, 20, 0, 100, 1, 1.2f, 2);
	ataques[31] = Attack("Empezamos Tema Nuevo", Support, 5, 5, 0, 100, 1.4f, 1, 1.1f);

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
	player->addAttack(ataques[PINCHO_ELIPTICO], 4);
	player->addAttack(ataques[CIRCULO_PERFECTO], 4);
	player->addAttack(ataques[ALUSIONES_FAMILIARES], 4);
	player->addAttack(ataques[EXPLORAR_LUGARES], 4);

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
			enemy->addAttack(e_ataques[rnd], 2);
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
	bool endBattle = false;

	if (player->getHealth() > 0 && enemy->getHealth() > 0)
	{
		std::cout << std::endl;

		//handleInput();
		while (!player->useAttack(input)) {
			std::cout << "No quedan PP para este ataque!" << std::endl;
		}

		float dmg = player->combat(input, enemy->getDefense(), enemy->getType());
		if (player->hasTarget())
		{
			enemy->receiveDamage(dmg);
			Attack temp_a = player->getAttack(input);
			enemy->receiveFactors(temp_a.atk_factor, temp_a.def_factor, temp_a.prc_factor);
		}

		std::cout << std::endl;

		if (enemy->getHealth() > 0)
		{
			enemy->useAttack(0);
			int e_input = enemy->getInput();
			dmg = enemy->combat(e_input, player->getDefense(), player->getType());
			if (enemy->hasTarget())
			{
				player->receiveDamage(dmg);
				Attack temp_a = enemy->getAttack(e_input);
				player->receiveFactors(temp_a.atk_factor, temp_a.def_factor, temp_a.prc_factor);
			}
		}

		std::cout << player->getName() << ": " << player->getHealth() << " HP" << std::endl;
		std::cout << enemy->getName() << ": " << enemy->getHealth() << " HP" << std::endl;

		std::cout << std::endl << "-------------------------------------------------------------" << std::endl;

		Attacking_ = false;
	}

	if (player->getHealth() > 0 && enemy->getHealth() <= 0) {
		std::cout << "HAS GANADO!" << std::endl;
		endBattle = true;
	}
	else if (player->getHealth() <= 0 && enemy->getHealth() > 0) {
		std::cout << "HAS PERDIDO!" << std::endl;
		endBattle = true;
	}
	else if (player->getHealth() <= 0 && enemy->getHealth() <= 0) {
		std::cout << "WTF EMPATE LOCO!" << std::endl;
		endBattle = true;
	}
	return endBattle;
}

void BattleState::createCharacterInfo()
{
	Vector2D position0;

	//Cuadro Jugador
	GameComponent* UI_Player = new GameComponent();
	position0.setX(0.15); position0.setY(0.2);
	UI_Player->setTextureId("26");
	UI_Player->setWidth(340); UI_Player->setHeight((150));
	UI_Player->setPosition(position0);
	UI_Player->addRenderComponent(rcF);
	stage.push_back(UI_Player);

	//Cuadro Enemigo
	GameComponent* UI_Enemy = new GameComponent();
	position0.setX(2.6); position0.setY(0.2);
	UI_Enemy->setTextureId("25");;
	UI_Enemy->setWidth(340); UI_Enemy->setHeight((150));
	UI_Enemy->setPosition(position0);
	UI_Enemy->addRenderComponent(rcF);
	stage.push_back(UI_Enemy);

	updateVidas();
}

void BattleState::createBattleButtons()
{
	Vector2D position0;
	double buttonWidth = 230;
	double buttonHeight = 75;

	//Boton 0
	interfaz.button_0 = new Button("19", nullptr, 0);
	position0.setX(3); position0.setY(7.2);
	interfaz.button_0->setPosition(position0); interfaz.button_0->setWidth(buttonWidth); interfaz.button_0->setHeight(buttonHeight);
	//interfaz.button_0->addRenderComponent(rcF);
	interfaz.button_0->addInputComponent(MIC);
	//stage.push_back(interfaz.button_0);

	//Boton 1
	interfaz.button_1 = new Button("19", nullptr, 1);
	position0.setX(4.2); position0.setY(7.2);
	interfaz.button_1->setPosition(position0); interfaz.button_1->setWidth(buttonWidth); interfaz.button_1->setHeight(buttonHeight);
	//interfaz.button_1->addRenderComponent(rcF); 
	interfaz.button_1->addInputComponent(MIC);
	//stage.push_back(interfaz.button_1);

	//Boton 2
	interfaz.button_2 = new Button("19", nullptr, 2);
	position0.setX(3); position0.setY(8.4);
	//interfaz.button_2->addRenderComponent(rcF);
	interfaz.button_2->setPosition(position0); interfaz.button_2->setWidth(buttonWidth); interfaz.button_2->setHeight(buttonHeight);
	interfaz.button_2->addInputComponent(MIC);
	//stage.push_back(interfaz.button_2);

	//Boton 3
	interfaz.button_3 = new Button("19", nullptr, 3);
	position0.setX(4.2); position0.setY(8.4);
	interfaz.button_3->setPosition(position0); interfaz.button_3->setWidth(buttonWidth); interfaz.button_3->setHeight(buttonHeight);
	//interfaz.button_3->addRenderComponent(rcF); 
	interfaz.button_3->addInputComponent(MIC);
	//stage.push_back(interfaz.button_3);

	//Boton Testeo Barra Vida
	/*Button* test = new Button(game, reduceVida, 4);
	position0.setX(2); position0.setY(4.4);
	test->setText(interfaz.botones); test->setPosition(position0); test->setWidth(buttonWidth); test->setHeight(buttonHeight);
	test->addRenderComponent(rcF); test->addInputComponent(MIC);
	stage.push_back(test);*/
}

void BattleState::updateVidas()
{
	interfaz.UI_Vida_Player = new GameComponent();
	interfaz.UI_Vida_Enemy = new GameComponent();

	Vector2D position0(0.86, 13.8);
	interfaz.VPlayer_position = position0;
	Vector2D position1(6.07, 13.8);
	interfaz.VEnemy_position = position1;

	interfaz.UI_Vida_Player->setTextureId("20");
	interfaz.UI_Vida_Player->setWidth(interfaz.Vida_Width); interfaz.UI_Vida_Player->setHeight((interfaz.Vida_height));
	interfaz.UI_Vida_Player->setPosition(interfaz.VPlayer_position);
	interfaz.UI_Vida_Player->addRenderComponent(rcF);

	interfaz.UI_Vida_Enemy->setTextureId("20");
	interfaz.UI_Vida_Enemy->setWidth(interfaz.Vida_Width); interfaz.UI_Vida_Enemy->setHeight((interfaz.Vida_height));
	interfaz.UI_Vida_Enemy->setPosition(interfaz.VEnemy_position);
	interfaz.UI_Vida_Enemy->addRenderComponent(rcF);

	stage.push_back(interfaz.UI_Vida_Player);
	stage.push_back(interfaz.UI_Vida_Enemy);
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

	if (!fade2Done_ && fadeDone_)
		init();
	else if (fade2Done_) {
		GameState::update();
		if (!END_ && Attacking_)
			END_ = run();
	}
	if (END_)
		Game::Instance()->getStateMachine()->popState();
}

void BattleState::render() {
	if (!fadeDone_ && !fade2Done_) {
		stage[stage.size() - 1]->render();
		fadeDone_ = true;
	}
	else {
		GameState::render();
	}
}

bool BattleState::handleEvent(const SDL_Event& event) {
	bool handledEvent = false;
	bool actButton = false;

	if (fade2Done_) {
		handledEvent = GameState::handleEvent(event);

		actButton = interfaz.button_0->handleEvent(event);
		if (actButton && !attack_) {
			toAttackMode();
		}
		else if (actButton && attack_) {
			attack(0);
		}

		actButton = interfaz.button_1->handleEvent(event);
		if (actButton && !attack_) {
			bag_ = true;
		}
		else if (actButton && attack_) {
			attack(1);
		}

		actButton = interfaz.button_2->handleEvent(event);
		if (actButton && !attack_) {
			toAttackMode();
		}
		else if (actButton && attack_) {
			attack(2);
		}

		actButton = interfaz.button_3->handleEvent(event);
		if (actButton && !attack_) {
			run_ = true;
			Game::Instance()->getStateMachine()->popState();
		}
		else if (actButton && attack_) {
			attack(3);
		}
	}

	return handledEvent || actButton;
}

void BattleState::attack(int i) {
	//antes de nada le quitamos el comp
	//ASEGURA QUE ERASE HACE EL DELETE
	player->delPhysicsComponent(mc);

	stage[1]->setTextureId("24");
	input = i;
	Attacking_ = true;
	attack_ = false; bag_ = false; run_ = false;

	Vector2D p = player->getPosition();
	Vector2D e = enemy->getPosition();
	mc = new MoveToThisPosComponent(p, e);
	player->addPhysicsComponent(mc);
}

void BattleState::toAttackMode() {
	attack_ = true;
	displayAttacks();
	stage[1]->setTextureId("29");
}