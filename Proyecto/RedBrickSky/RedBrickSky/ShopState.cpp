#pragma once

#include "ShopState.h"

ShopState::ShopState()
{
	ShopItems* items = new ShopItems();
	shopObjects = items->getItems();
	delete items;

	SDL_ShowCursor(1);

	invent = GameManager::Instance()->copyInventory();
	money = GameManager::Instance()->getMoney();

	StringToScreen::Instance()->pushInfinite("Caramelos: " + std::to_string(money), 320,400);

	//Componentes necesarios

	//Separamos elementos dependiendo de su clase
	separateElements();

	//Imagen de fondo de la tienda
	GameComponent* backShop = new GameComponent();
	backShop->setTextureId("shop1"); backShop->addRenderComponent(new RenderFullComponent());
	stage.push_back(backShop);

	//Creamos la matiz y la llenamos de StandPoints
	createSP();

	//Creaci�n de los items que tendr� la tienda
	createShopItems();

	GameComponent* frontShop = new GameComponent();
	frontShop->setTextureId("shop2"); frontShop->addRenderComponent(new RenderFullComponent());
	stage.push_back(frontShop);

	//Creamos la imagen que va por encima de la mochila para que no se vea al hacer scroll
	/*GameComponent* frontShop = new GameComponent();
	frontShop->setTextureId("7"); frontShop->addRenderComponent(rc);
	stage.push_back(frontShop);*/

	//Creamos bot�n para volver al men� principal
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
	SDL_ShowCursor(0);
	StringToScreen::Instance()->clearInfinite();
	StringToScreen::Instance()->stopRendering();
}

void ShopState::setSP(vector<estado> s) {

	destroySP();
	for (int i = 0; i < s.size(); i++)
		SP.push_back(s[i]);
}

void ShopState::separateElements() {
	//Guardamos los elementos del inventario en sus correspondientes vectores
	Weapons.clear();
	Potions.clear();
	Objects.clear();
	for (unsigned int i = 0; i < invent.size(); i++) {
		if (invent[i].type == 0)
			Weapons.push_back(invent[i]);
		else if (invent[i].type == 1)
			Potions.push_back(invent[i]);
		else if (invent[i].type == 2)
			Objects.push_back(invent[i]);

		ocupados++;
	}
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

		Vector2D position5(k - 1 + shopCols, 3 * j);
		Vector2D oriPos(k - 1 + shopCols, 3 * j);

		//Crea objetos debajo de los anteriores que no se mover�n, ser�n solo imagen
		GameComponent* gc2 = new GameComponent();
		gc2->setTextureId(shopObjects[i].tx); gc2->setOriPos(oriPos); gc2->setPosition(position5); gc2->setWidth(50); gc2->setHeight(50);
		gc2->addRenderComponent(new RenderSingleFrameComponent()); gc2->addInputComponent(new MouseScrollShopComponent(this));
		gc2->setColFrame(shopObjects[i].colFrame); gc2->setRowFrame(shopObjects[i].FilFrame);
		
		//Crea los objetos de la tienda que se mueden mover
		GameComponent* gc = new GameComponent();
		DragNDropShopComponent* p = new DragNDropShopComponent(this, shopObjects[i].price, false, shopObjects[i].ID, gc, shopObjects[i].type, shopObjects[i].nombre, shopObjects[i].FilFrame, shopObjects[i].colFrame);
		gc->setTextureId(shopObjects[i].tx); gc->setOriPos(oriPos); gc->setPosition(position5); gc->setWidth(50); gc->setHeight(50);
		gc->addRenderComponent(new RenderSingleFrameComponent()); gc->addInputComponent(p); gc->addInputComponent(new MouseInfoClickComponent(shopObjects[i], this));	gc->addInputComponent(new MouseScrollShopComponent(this));
		gc->setColFrame(shopObjects[i].colFrame); gc->setRowFrame(shopObjects[i].FilFrame);


		stageBack(gc2); //A�adimos la imagen de detr�s del objeto al stage
		stageBack(gc); //A�adimos el objeto
		GCshopV.push_back(gc); //A�adimos el elemento al vector de Items de la tienda
		k++;

	}

	//Creamos el elemento que nos permitir� movernos con teclado y con el mandop
	selector_ = new GameComponent();
	Vector2D selecPos;
	selecPos.set(7, 3);

	selector_->setTextureId("12"); selector_->setPosition(selecPos);
	selector_->setWidth(50); selector_->setHeight(50);
	selector_->addRenderComponent(new RenderSingleFrameComponent()); selector_->addInputComponent(new KeyBoardShopComponent(selecPos.getX(), selecPos.getY(), shopCols, 6, 2, StandPointsO, nullptr, this));
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

		if (invent[i].type != 2) {
			SP[i].ID = invent[i].ID;
			SP[i].objects++;
			SP[i].empty = false;
			SP[i].comprado = true;
			SP[i].price = invent[i].price;
			SP[i].tx = invent[i].tx;
			SP[i].type = invent[i].type;

			GameComponent* gc = new GameComponent();
			Vector2D position0(SP[i].y - 2.8, SP[i].x + 2.8);
			double width = invent[i].w;
			double height = invent[i].h;

			gc->setTextureId(invent[i].tx); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
			gc->addRenderComponent(new RenderSingleFrameComponent); gc->addInputComponent(new MouseScrollShopComponent(this));  gc->addInputComponent(new MouseInfoClickComponent(invent[i], this));
			gc->setColFrame(invent[i].colFrame); gc->setRowFrame(invent[i].FilFrame);

			stage.push_back(gc);
			GCInventV.push_back(gc);

			ocupados++;

			k++;
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
	double width = 50;
	double height = 50;
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


			Vector2D position0(2 * i + 0.7, 2 * j + 3.5);
			if (i == 0 && j == 0)
				selecPos = position0;
			if (i == 1 && j == 0)
				auxD = position0.getX() - selecPos.getX();

			s.x = position0.getX();
			s.y = position0.getY();
			GameComponent* gc = new GameComponent();
			InputComponent* auxSCP = new MouseScrollShopComponent(this, auxOID);

			gc->setTextureId("8"); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
			
			gc->addRenderComponent(new RenderSingleFrameComponent()); gc->addInputComponent(auxSCP);//  gc->addInputComponent(InventoryShopFBcomponent());

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
	// 1) Comprueba las teclas de acceso a los distintos men�s, etc.
		if (event.type == SDL_KEYDOWN)
		 {
			if (event.key.keysym.sym == SDLK_ESCAPE)
				toMenu();
			}
		// 2) LLama a los input de cada objeto del propio estado
		return GameState::handleEvent(event);
	}


