#pragma once

#include "ShopState.h"

ShopState::ShopState()
{
	shopObjects = GameManager::Instance()->copyShopItems();
	
	SDL_ShowCursor(1);

	invent = GameManager::Instance()->copyInventory();
	money = GameManager::Instance()->getMoney();

	
	StringToScreen::Instance()->pushInfinite("Caramelos: " + std::to_string(money), 350, 395);
	StringToScreen::Instance()->pushInfinite("Comprar pociones      x" + std::to_string(GameManager::Instance()->getPotions()), 350, 320);
	

	//Imagen de fondo de la tienda
	GameComponent* backShop = new GameComponent();
	backShop->setTextureId("shop1"); backShop->addRenderComponent(new RenderFullComponent());
	stage.push_back(backShop);

	//Creamos la matiz y la llenamos de StandPoints
	createSP();

	//Creación de los items que tendrá la tienda
	createShopItems();

	//Creamos botón para volver al menú principal
	mainMenuBotton();
}

void ShopState::setMoney(int n) {

	money = money - n;
	GameManager::Instance()->setMoney(money);
}

void ShopState::toMenu() {
	StateMachine* sm = Game::Instance()->getStateMachine(); 
	sm->popState();
}

ShopState::~ShopState()
{
	GameManager::Instance()->changeShopItems(shopObjects);
	SDL_ShowCursor(0);
	StringToScreen::Instance()->clearInfinite();
	StringToScreen::Instance()->stopRendering();
}

void ShopState::setSP(vector<estado> s) {

	destroySP();
	for (int i = 0; i < s.size(); i++)
		SP.push_back(s[i]);
}


void ShopState::mainMenuBotton() {

	Button* bottonBack = new Button("3", toMenu, 0);

	Vector2D position0(11, 0.5);

	double width = 100;
	double height = 60;

	bottonBack->setPosition(position0); bottonBack->setWidth(width); bottonBack->setHeight(height);
	bottonBack->addRenderComponent(new RenderFrameComponent()); bottonBack->addInputComponent(new MouseInputComponentButton());

	stage.push_back(bottonBack);
}

void ShopState::createShopItems() {
	int j = 0;
	int k = 0;
	int shopCols = 8;

	for (unsigned int i = 0; i < shopObjects.size(); i++) {

		if (i % shopCols == 0) {
			j++;
			k = 0;
		}

		Vector2D position5(k - 1 + shopCols, 1.5 * j + 1);
		Vector2D oriPos(k - 1 + shopCols, 1.5 * j + 1);

		//Crea objetos debajo de los anteriores que no se moverán, serán solo imagen
		GameComponent* gc2 = new GameComponent();
		gc2->setTextureId(shopObjects[i].tx); gc2->setOriPos(oriPos); gc2->setPosition(position5); gc2->setWidth(50); gc2->setHeight(50);
		gc2->addRenderComponent(new RenderSingleFrameComponent());
		gc2->setColFrame(shopObjects[i].colFrame); gc2->setRowFrame(shopObjects[i].FilFrame);

		//Crea los objetos de la tienda que se mueden mover
		GameComponent* gc = new GameComponent();
		DragNDropShopComponent* p = new DragNDropShopComponent(this, shopObjects[i].price, shopObjects[i].comprado, shopObjects[i].ID, gc, shopObjects[i].type, shopObjects[i].nombre, shopObjects[i].FilFrame, shopObjects[i].colFrame);
		gc->setTextureId(shopObjects[i].tx); gc->setOriPos(oriPos); gc->setPosition(position5); gc->setWidth(50); gc->setHeight(50);
		gc->addRenderComponent(new RenderSingleFrameComponent()); gc->addInputComponent(p); gc->addInputComponent(new MouseInfoClickComponent(shopObjects[i], this));
		gc->setColFrame(shopObjects[i].colFrame); gc->setRowFrame(shopObjects[i].FilFrame);

		stageBack(gc2); //Añadimos la imagen de detrás del objeto al stage
		stageBack(gc); //Añadimos el objeto
		GCshopV.push_back(gc); //Añadimos el elemento al vector de Items de la tienda

		k++;

	}


	estado s;
	s.empty = false;
	s.comprado = false;
	s.ID = 15;
	s.objects = 1;
	s.price = GameManager::Instance()->getPotionsPrize();
	s.tx = "21";
	s.type = 1; //Es una pocion
	s.nombre = "Pocion de vida";
	s.colFrame = 0;
	s.FilFrame = 4;

	Vector2D v; v.set(12, 6.5);
	//Crea los objetos de la tienda que se mueden mover
	GameComponent* gc = new GameComponent();
	ShopState* shopit = this;

	gc->setTextureId(s.tx); gc->setOriPos(v); gc->setPosition(v); gc->setWidth(50); gc->setHeight(50);
	gc->addRenderComponent(new RenderSingleFrameComponent()); gc->addInputComponent(new MouseInfoClickComponent(s, shopit));
	gc->setColFrame(s.colFrame); gc->setRowFrame(s.FilFrame);
	stageBack(gc); //Añadimos el objeto


	//Crea el boton para comprar la pocion
	GameComponent* poti = new GameComponent();
	Vector2D p(0.78, 4.5);
	poti->setTextureId("potiFB"); poti->setOriPos(p); poti->setPosition(p); poti->setWidth(435); poti->setHeight(70);
	poti->addRenderComponent(new RenderSingleFrameComponent()); poti->addInputComponent(new PotionShop());
	poti->setColFrame(0); poti->setRowFrame(0);
	stageBack(poti);

	//Creamos el elemento que nos permitirá movernos con teclado y con el mandop
	selector_ = new GameComponent();
	Vector2D selecPos;
	selecPos.set(7, 2.5);

	selector_->setTextureId("12"); selector_->setPosition(selecPos);
	selector_->setWidth(50); selector_->setHeight(50);
	selector_->addRenderComponent(new RenderSingleFrameComponent()); selector_->addInputComponent(new KeyBoardShopComponent(selecPos.getX(), selecPos.getY(), 8, 4,2, StandPointsO, nullptr, this));
	InputComponent* xbox = new ShopXboxControllerComponent(selecPos.getX(), selecPos.getY(), shopCols, 6, 2, StandPointsO, nullptr, this);
	selector_->setColFrame(0); selector_->setRowFrame(0);
	selector_->addInputComponent(xbox);

	stage.push_back(selector_);
}

void ShopState::createBagItems() {
	int k = 0;
	int j = 0;
	ocupados = 0;
	for (unsigned int i = 0; i < invent.size(); i++) {

		if (j == 3) { j = 0; k++; }
		if (invent[i].type != 2 && invent[i].type != 1) {
			SP[i].ID = invent[i].ID;
			SP[i].objects++;
			SP[i].empty = false;
			SP[i].comprado = true;
			SP[i].price = invent[i].price;
			SP[i].tx = invent[i].tx;
			SP[i].type = invent[i].type;

			GameComponent* gc = new GameComponent();
			Vector2D position0(2 * j + 1.2, 1.7 * k + 2.5);
			j++;
			double width = invent[i].w;
			double height = invent[i].h;

			gc->setTextureId(invent[i].tx); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
			gc->addRenderComponent(new RenderSingleFrameComponent); gc->addInputComponent(new MouseInfoClickComponent(invent[i], this));
			gc->setColFrame(invent[i].colFrame); gc->setRowFrame(invent[i].FilFrame);

			stage.push_back(gc);
			GCInventV.push_back(gc);

			ocupados++;
		}
	}
}

void ShopState::destroySP() {

	SP.clear();
}

void ShopState::createSP() {
	//Creamos los SP
	destroySP();
	Vector2D selecPos;
	int auxD = 0;
	auxOID = 0;
	numSP = 0;
	double width = 45;
	double height = 45;
	for (int i = 0; i < Fils; i++)
		for (int j = 0; j < Cols; j++) {

			estado s;

			s.empty = true;
			s.ID = 0;
			s.objects = 0;
			s.w = width;
			s.h = height;
			s.mX = i;
			s.mY = j;
			s.objectID = auxOID;
			s.type = -1;

			Vector2D position0(2 * i + 1.2, 1.7 * j + 2.5);
			if (i == 0 && j == 0)
				selecPos = position0;
			if (i == 1 && j == 0)
				auxD = position0.getX() - selecPos.getX();

			s.x = position0.getX();
			s.y = position0.getY();
			GameComponent* gc = new GameComponent();

			gc->setTextureId("8"); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);

			gc->addRenderComponent(new RenderSingleFrameComponent());

			stage.push_back(gc);
			SP.push_back(s);
			StandPointsO.push_back(gc);

			numSP++;
			auxOID++;
		}
	ultimaFilaY = Fils;

	//Creamos los elementos de la mochila
	createBagItems();
}

bool ShopState::handleEvent(const SDL_Event & event)
{
	// 1) Comprueba las teclas de acceso a los distintos menús, etc.
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			toMenu();
	}

	// 2) LLama a los input de cada objeto del propio estado
	return GameState::handleEvent(event);
}

void ShopState::setInvent(vector<estado> v) {
	invent.clear();
	for (int i = 0; i < v.size(); i++)
		invent.push_back(v[i]);
}
