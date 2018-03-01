#include "BattleState.h"

BattleState::BattleState(Game* gamePtr) : GameState (gamePtr)
{

	//Texturas necesitadas
	interfaz.cuadro_principal = gamePtr->getTexture(17);
	interfaz.cuadro_personaje = gamePtr->getTexture(19);
	interfaz.Vida = gamePtr->getTexture(20);
	interfaz.botones = gamePtr->getTexture(18);

	game = gamePtr;

	//Componentes necesarios
	rcF = new RenderFrameComponent(); //Render Frame
	rc = new RenderFullComponent(); //Render FS
	Info = new MouseInfoClickComponent();
	MIC = new MouseInputComponentButton();

	createUI();
}

BattleState::~BattleState()
{
}

void BattleState::buttonsToAttack(Game* gamePtr) {
	/*interfaz.button_0 = new Button(game, XXXXXXX, 0);
	interfaz.button_1 = new Button(game, XXXXXXX, 1);
	interfaz.button_2 = new Button(game, XXXXXXX, 2);
	interfaz.button_3 = new Button(game, XXXXXXX, 3);*/
}

void BattleState::tryEscape(Game* gamePtr) {
	
	//Aquí iría la comprobación aleatoria de "Has logrado escapar!" o "Eres un pringado y tienes que luchar!"
	
	StateMachine* sm = gamePtr->getStateMachine();
	sm->popState();
}

void BattleState::usePotion(Game* gamePtr) {
	//PSEUDOCODIGO
	/*if (puntero_a_player->tienePociones && puntero_a_player->getVida != MAXIMA) {
	puntero_a_player->inventario.pociones -= 1;
	puntero_a_player->vida += valor_pociones;
	}*/
}

void BattleState::specialAttack(Game* gamePtr) {

}

void BattleState::attack1(Game * gamePtr)
{
}

void BattleState::attack2(Game * gamePtr)
{
}

void BattleState::attack3(Game * gamePtr)
{
}

void BattleState::attack4(Game * gamePtr)
{
}

void BattleState::createUI() {

	//Panel de fondo
	Vector2D position0(0, 2.6);
	GameComponent* UI_Background = new GameComponent(game);
	UI_Background->setText(interfaz.cuadro_principal);
	UI_Background->setWidth(game->getWinWidth()); UI_Background->setHeight((200));
	UI_Background->setPosition(position0);
	UI_Background->addRenderComponent(rcF);
	stage.push_back(UI_Background);

	createCharacterInfo();
	createBattleButtons();


	/*GameComponent* UI_Text = new GameComponent(game);
	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
	SDL_Color Black = { 0, 0, 0 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Aquí van los mensajes de batalla", Black);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);*/

}

void BattleState::createCharacterInfo()
{
	Vector2D position0;

	//Cuadro Jugador
	GameComponent* UI_Player = new GameComponent(game);
	position0.setX(0.5); position0.setY(0.5);
	UI_Player->setText(interfaz.cuadro_personaje);
	UI_Player->setWidth(200); UI_Player->setHeight((120));
	UI_Player->setPosition(position0);
	UI_Player->addRenderComponent(rcF);
	stage.push_back(UI_Player);

	//Cuadro Enemigo
	GameComponent* UI_Enemy = new GameComponent(game);
	position0.setX(4.8); position0.setY(0.5);
	UI_Enemy->setText(interfaz.cuadro_personaje);
	UI_Enemy->setWidth(200); UI_Enemy->setHeight((120));
	UI_Enemy->setPosition(position0);
	UI_Enemy->addRenderComponent(rcF);
	stage.push_back(UI_Enemy);

	//Vidas
	interfaz.UI_Vida_Player = new GameComponent(game);
	interfaz.UI_Vida_Enemy = new GameComponent(game);

	position0.setX(0.75); position0.setY(6.6);
	interfaz.VPlayer_position = position0;
	Vector2D position1(6.13, 6.6);
	interfaz.VEnemy_position = position1;
	interfaz.Vida_Width = 160;

	interfaz.UI_Vida_Player->setText(interfaz.Vida);
	interfaz.UI_Vida_Player->setWidth(interfaz.Vida_Width); interfaz.UI_Vida_Player->setHeight((20));
	interfaz.UI_Vida_Player->setPosition(interfaz.VPlayer_position);
	interfaz.UI_Vida_Player->addRenderComponent(rcF);

	interfaz.UI_Vida_Enemy->setText(interfaz.Vida);
	interfaz.UI_Vida_Enemy->setWidth(interfaz.Vida_Width); interfaz.UI_Vida_Enemy->setHeight((20));
	interfaz.UI_Vida_Enemy->setPosition(interfaz.VEnemy_position);
	interfaz.UI_Vida_Enemy->addRenderComponent(rcF);

	stage.push_back(interfaz.UI_Vida_Player);
	stage.push_back(interfaz.UI_Vida_Enemy);
}

void BattleState::createBattleButtons()
{
	clearButtons();
	Vector2D position0;
	double buttonWidth = 230;
	double buttonHeight = 75;

	//Boton 0
	interfaz.button_0 = new Button(game, buttonsToAttack, 0);
	position0.setX(3); position0.setY(7.2);
	interfaz.button_0->setText(interfaz.botones); interfaz.button_0->setPosition(position0); interfaz.button_0->setWidth(buttonWidth); interfaz.button_0->setHeight(buttonHeight);
	interfaz.button_0->addRenderComponent(rcF); interfaz.button_0->addInputComponent(MIC);
	stage.push_back(interfaz.button_0);

	//Boton 1
	interfaz.button_1 = new Button(game, tryEscape, 1);
	position0.setX(4.2); position0.setY(7.2);
	interfaz.button_1->setText(interfaz.botones); interfaz.button_1->setPosition(position0); interfaz.button_1->setWidth(buttonWidth); interfaz.button_1->setHeight(buttonHeight);
	interfaz.button_1->addRenderComponent(rcF); interfaz.button_1->addInputComponent(MIC);
	stage.push_back(interfaz.button_1);

	//Boton 2
	interfaz.button_2 = new Button(game, usePotion, 2);
	position0.setX(3); position0.setY(8.4);
	interfaz.button_2->setText(interfaz.botones); interfaz.button_2->setPosition(position0); interfaz.button_2->setWidth(buttonWidth); interfaz.button_2->setHeight(buttonHeight);
	interfaz.button_2->addRenderComponent(rcF); interfaz.button_2->addInputComponent(MIC);
	stage.push_back(interfaz.button_2);

	//Boton 3
	interfaz.button_3 = new Button(game, specialAttack, 3);
	position0.setX(4.2); position0.setY(8.4);
	interfaz.button_3->setText(interfaz.botones); interfaz.button_3->setPosition(position0); interfaz.button_3->setWidth(buttonWidth); interfaz.button_3->setHeight(buttonHeight);
	interfaz.button_3->addRenderComponent(rcF); interfaz.button_3->addInputComponent(MIC);
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
	clearButtons();
	Vector2D position0;
	double buttonWidth = 230;
	double buttonHeight = 75;

	//Boton 0
	interfaz.button_0 = new Button(game, attack1, 0);
	position0.setX(3); position0.setY(7.2);
	interfaz.button_0->setText(interfaz.botones); interfaz.button_0->setPosition(position0); interfaz.button_0->setWidth(buttonWidth); interfaz.button_0->setHeight(buttonHeight);
	interfaz.button_0->addRenderComponent(rcF); interfaz.button_0->addInputComponent(MIC);
	stage.push_back(interfaz.button_0);

	//Boton 1
	interfaz.button_1 = new Button(game, attack2, 1);
	position0.setX(4.2); position0.setY(7.2);
	interfaz.button_1->setText(interfaz.botones); interfaz.button_1->setPosition(position0); interfaz.button_1->setWidth(buttonWidth); interfaz.button_1->setHeight(buttonHeight);
	interfaz.button_1->addRenderComponent(rcF); interfaz.button_1->addInputComponent(MIC);
	stage.push_back(interfaz.button_1);

	//Boton 2
	interfaz.button_2 = new Button(game, attack3, 2);
	position0.setX(3); position0.setY(8.4);
	interfaz.button_2->setText(interfaz.botones); interfaz.button_2->setPosition(position0); interfaz.button_2->setWidth(buttonWidth); interfaz.button_2->setHeight(buttonHeight);
	interfaz.button_2->addRenderComponent(rcF); interfaz.button_2->addInputComponent(MIC);
	stage.push_back(interfaz.button_2);

	//Boton 3
	interfaz.button_3 = new Button(game, attack4, 3);
	position0.setX(4.2); position0.setY(8.4);
	interfaz.button_3->setText(interfaz.botones); interfaz.button_3->setPosition(position0); interfaz.button_3->setWidth(buttonWidth); interfaz.button_3->setHeight(buttonHeight);
	interfaz.button_3->addRenderComponent(rcF); interfaz.button_3->addInputComponent(MIC);
	stage.push_back(interfaz.button_3);
}

void BattleState::updateVida(GameComponent* barraVida, double variacion)
{
	barraVida->setWidth(barraVida->getWidth()*variacion);
	Vector2D positionNew (barraVida->getPosition().getX() * (1 / variacion), barraVida->getPosition().getY());
	stage.push_back(barraVida);
}

void BattleState::reduceVida(Game* gamePtr)
{
	/*updateVida(interfaz.UI_Vida_Player, 0.25);*/
}

void BattleState::clearButtons()
{
	/*vector<GameObject*>::iterator it = stage.begin();

	while (it != stage.end()) {

		if (typeid(it) == typeid(Button())) {

			it = stage.erase(it);
		}
		else ++it;
	}*/
	//stage.erase(std::remove_if(stage.begin(), stage.end(), isButton), stage.end());
}

bool BattleState::isButton(GameObject * object)
{
	if ( typeid(object) == typeid(Button()) ) {
		return true;
	}
	return false;
}

void BattleState::update() {
	c.run();
	GameState::update();
}
