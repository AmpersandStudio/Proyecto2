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

	//JR para el inicio
	rcfade = new RenderFullComponent();
	alpha_ = 255;
	fade_ = new GameComponent();
	fade_->setTextureId("23");
	fade_->addRenderComponent(rcfade);
	fadeDone_ = false;
	fade2Done_ = false;

	//Componentes necesarios
	rcF = new RenderFrameComponent(); //Render Frame
	rc = new RenderFullComponent(); //Render FS
									//Info = new MouseInfoClickComponent();
	MIC = new MouseInputComponentButton();

	createUI();

}

BattleState::~BattleState()
{
	SDL_SetTextureAlphaMod(TheTextureManager::Instance()->getTexture("23"), 255); //para restaurar el alpha original
}

void BattleState::buttonsToAttack() {
	/*interfaz.button_0 = new Button(game, XXXXXXX, 0);
	interfaz.button_1 = new Button(game, XXXXXXX, 1);
	interfaz.button_2 = new Button(game, XXXXXXX, 2);
	interfaz.button_3 = new Button(game, XXXXXXX, 3);*/

	//totalmente consciente de la guarrada, solo es para probar
	GameState* gs = Game::Instance()->getStateMachine()->currentState();
	BattleState* bs = static_cast<BattleState*>(gs);
	bs->attackMode = !bs->attackMode;
}

void BattleState::tryEscape() {

	//Aquí iría la comprobación aleatoria de "Has logrado escapar!" o "Eres un pringado y tienes que luchar!"

	StateMachine* sm = Game::Instance()->getStateMachine();
	sm->popState();
}

void BattleState::usePotion() {
	//PSEUDOCODIGO
	/*if (puntero_a_player->tienePociones && puntero_a_player->getVida != MAXIMA) {
	puntero_a_player->inventario.pociones -= 1;
	puntero_a_player->vida += valor_pociones;
	}*/
}

void BattleState::specialAttack() {

}

void BattleState::attack1()
{
}

void BattleState::attack2()
{
}

void BattleState::attack3()
{
}

void BattleState::attack4()
{
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
	Vector2D pos(1, 1.5);
	ground->setPosition(pos);
	ground->setWidth(200); ground->setHeight(200);
	RenderComponent* rc = new RenderFrameComponent();
	ground->addRenderComponent(rc);
	stage.push_back(ground);

	GameComponent* ground2 = new GameComponent();
	ground2->setTextureId("27");
	Vector2D pos2(4.325, 1.5);
	ground2->setPosition(pos2);
	ground2->setWidth(200); ground2->setHeight(200);
	RenderComponent* rc2 = new RenderFrameComponent();
	ground2->addRenderComponent(rc2);
	stage.push_back(ground2);

	//fade inicial
	stage.push_back(fade_);
}

void BattleState::createCharacterInfo()
{
	Vector2D position0;

	//Cuadro Jugador
	GameComponent* UI_Player = new GameComponent();
	position0.setX(0.3); position0.setY(0.5);
	UI_Player->setTextureId("26");
	UI_Player->setWidth(340); UI_Player->setHeight((150));
	UI_Player->setPosition(position0);
	UI_Player->addRenderComponent(rcF);
	stage.push_back(UI_Player);

	//Cuadro Enemigo
	GameComponent* UI_Enemy = new GameComponent();
	position0.setX(2.45); position0.setY(0.5);
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
	interfaz.button_0 = new Button("28", buttonsToAttack, 0);
	position0.setX(3); position0.setY(3.6);
	interfaz.button_0->setPosition(position0); interfaz.button_0->setWidth(buttonWidth); interfaz.button_0->setHeight(buttonHeight*2);
	//interfaz.button_0->addRenderComponent(rcF);
	interfaz.button_0->addInputComponent(MIC);
	stage.push_back(interfaz.button_0);

	//Boton 1
	interfaz.button_1 = new Button("28", usePotion, 1);
	position0.setX(4.2); position0.setY(7.2);
	interfaz.button_1->setPosition(position0); interfaz.button_1->setWidth(buttonWidth); interfaz.button_1->setHeight(buttonHeight);
	//interfaz.button_1->addRenderComponent(rcF); 
	interfaz.button_1->addInputComponent(MIC);
	stage.push_back(interfaz.button_1);

	//Boton 2
	//interfaz.button_2 = new Button(game, specialAttack, 2);
	//position0.setX(3); position0.setY(8.4);
	//interfaz.button_2->setText(interfaz.botones); interfaz.button_2->setPosition(position0); interfaz.button_2->setWidth(buttonWidth); interfaz.button_2->setHeight(buttonHeight);
	//interfaz.button_2->addRenderComponent(rcF); interfaz.button_2->addInputComponent(MIC);
	//stage.push_back(interfaz.button_2);

	//Boton 3
	interfaz.button_3 = new Button("28", tryEscape, 3);
	position0.setX(4.2); position0.setY(8.4);
	interfaz.button_3->setPosition(position0); interfaz.button_3->setWidth(buttonWidth); interfaz.button_3->setHeight(buttonHeight);
	//interfaz.button_3->addRenderComponent(rcF); 
	interfaz.button_3->addInputComponent(MIC);
	stage.push_back(interfaz.button_3);

	//Boton Testeo Barra Vida
	/*Button* test = new Button(game, reduceVida, 4);
	position0.setX(2); position0.setY(4.4);
	test->setText(interfaz.botones); test->setPosition(position0); test->setWidth(buttonWidth); test->setHeight(buttonHeight);
	test->addRenderComponent(rcF); test->addInputComponent(MIC);
	stage.push_back(test);*/
}

void BattleState::createAttackButtons()
{
	Vector2D position0;
	double buttonWidth = 230;
	double buttonHeight = 75;

	//Boton 0
	interfaz.button_0 = new Button("28", attack1, 0);
	position0.setX(3); position0.setY(7.2);
	interfaz.button_0->setPosition(position0); interfaz.button_0->setWidth(buttonWidth); interfaz.button_0->setHeight(buttonHeight);
	interfaz.button_0->addRenderComponent(rcF); interfaz.button_0->addInputComponent(MIC);
	stage.push_back(interfaz.button_0);

	//Boton 1
	interfaz.button_1 = new Button("28", attack2, 1);
	position0.setX(4.2); position0.setY(7.2);
	interfaz.button_1->setPosition(position0); interfaz.button_1->setWidth(buttonWidth); interfaz.button_1->setHeight(buttonHeight);
	interfaz.button_1->addRenderComponent(rcF); interfaz.button_1->addInputComponent(MIC);
	stage.push_back(interfaz.button_1);

	//Boton 2
	interfaz.button_2 = new Button("28", attack3, 2);
	position0.setX(3); position0.setY(8.4);
	interfaz.button_2->setPosition(position0); interfaz.button_2->setWidth(buttonWidth); interfaz.button_2->setHeight(buttonHeight);
	interfaz.button_2->addRenderComponent(rcF); interfaz.button_2->addInputComponent(MIC);
	stage.push_back(interfaz.button_2);

	//Boton 3
	interfaz.button_3 = new Button("28", attack4, 3);
	position0.setX(4.2); position0.setY(8.4);
	interfaz.button_3->setPosition(position0); interfaz.button_3->setWidth(buttonWidth); interfaz.button_3->setHeight(buttonHeight);
	interfaz.button_3->addRenderComponent(rcF); interfaz.button_3->addInputComponent(MIC);
	stage.push_back(interfaz.button_3);
}

void BattleState::updateVidas()
{
	interfaz.UI_Vida_Player = new GameComponent();
	interfaz.UI_Vida_Enemy = new GameComponent();

	Vector2D position0(1.25, 8);
	interfaz.VPlayer_position = position0;
	Vector2D position1(5.65, 8);
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
	SDL_SetTextureAlphaMod(TheTextureManager::Instance()->getTexture("28"), 50); //para delimitar los botones
	
	//para comprobar el cambio de textura
	if (!attackMode)
		stage[0]->setTextureId("24"); 
	else
		stage[0]->setTextureId("29");

	if (!fade2Done_ && fadeDone_)
		init();
	else if (fade2Done_) {
		GameState::update();
	}
}

void BattleState::render() {
	if (!fadeDone_ && !fade2Done_) {
		stage[stage.size() - 1]->render();
		fadeDone_ = true;
	}
	else
		GameState::render();
}

bool BattleState::handleEvent(SDL_Event& event) {
	bool handledEvent = false;

	if (fade2Done_)
		handledEvent = GameState::handleEvent(event);

	return handledEvent;
}
