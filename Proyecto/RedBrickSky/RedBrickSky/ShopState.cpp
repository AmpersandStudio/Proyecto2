#pragma once

#include "ShopState.h"
#include "Button.h"
#include <iostream>
#include "InventoryShopFBcomponent.h"

ShopState::ShopState(Game* gamePtr) : GameState(gamePtr)
{
	game = gamePtr;

	ShopItems* items = new ShopItems(game);
	shopObjects = items->getItems();

	invent = GameManager::Instance()->copyInventory();
	money = GameManager::Instance()->getMoney();
	std::cout << "Tu dinero actual es: " << money << std::endl;

	//Texturas necesitadas
	back = gamePtr->getTexture(6);
	standPoint = gamePtr->getTexture(8);
	front = gamePtr->getTexture(7);
	bot = gamePtr->getTexture(3); //Para el bot�n

	//Componentes necesarios
	rcF = new RenderFrameComponent(); //Render Frame
	rc = new RenderFullComponent(); //Render FS
	MSC = new MouseScrollShopComponent(this);
	//MSOC = new MouseOverObjectComponent();
	MIC = new MouseInputComponentButton();

	//Separamos elementos dependiendo de su clase
	separateElements();

	//Imagen de fondo de la tienda
	GameComponent* backShop = new GameComponent(game);
	backShop->setText(back); backShop->addRenderComponent(rc);
	stage.push_back(backShop);

	//Creamos la matiz y la llenamos de StandPoints
	createMatrix();

	//Creaci�n de los items que tendr� la tienda
	createShopItems();

	//Creamos la imagen que va por encima de la mochila para que no se vea al hacer scroll
	GameComponent* frontShop = new GameComponent(game);
	frontShop->setText(front); frontShop->addRenderComponent(rc);
	stage.push_back(frontShop);

	//Creamos bot�n para volver al men� principal
	mainMenuBotton();

}

void ShopState::setMoney(int n) {

	money = money - n;
	GameManager::Instance()->setMoney(money);
}

void ShopState::toMenu(Game* game) {
	
	StateMachine* sm = game->getStateMachine();
	sm->popState();
}

ShopState::~ShopState()
{

}

void ShopState::setSP(vector<estado> s) {

	SP.clear();
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

	Button* bottonBack = new Button(game, toMenu, 0);

	Vector2D position0(7, 6);

	double width = 150;
	double height = 100;

	bottonBack->setText(bot); bottonBack->setPosition(position0); bottonBack->setWidth(width); bottonBack->setHeight(height);
	bottonBack->addRenderComponent(rcF); bottonBack->addInputComponent(MIC);

	stage.push_back(bottonBack);
}

void ShopState::createShopItems() {
	int j = 0;
	int k = 0;

	for (int i = 0; i < shopObjects.size(); i++) {

		if (i % 5 == 0) {
			j++;
			k = 0;
		}

		//Crea los objetos de la tienda que se mueden mover
		GameComponent* gc = new GameComponent(game);
		Vector2D position5(k + 10, 2 * j);
		Vector2D oriPos(k + 10, 2 * j);
		DragNDropShopComponent* p = new DragNDropShopComponent(this, shopObjects[i].price, false, shopObjects[i].ID, gc, shopObjects[i].type, shopObjects[i].nombre, shopObjects[i].FilFrame, shopObjects[i].colFrame);
		gc->setText(shopObjects[i].tx); gc->setOriPos(oriPos); gc->setPosition(position5); gc->setWidth(70); gc->setHeight(70);
		gc->addRenderComponent(rcF); gc->addInputComponent(p); gc->addInputComponent(new MouseInfoClickComponent(shopObjects[i]));	gc->addInputComponent(MSC);
		gc->setColFrame(shopObjects[i].colFrame); gc->setRowFrame(shopObjects[i].FilFrame);

		//Crea objetos debajo de los anteriores que no se mover�n, ser�n solo imagen
		GameComponent* gc2 = new GameComponent(game);
		gc2->setText(shopObjects[i].tx); gc2->setOriPos(oriPos); gc2->setPosition(position5); gc2->setWidth(70); gc2->setHeight(70);
		gc2->addRenderComponent(rcF); gc2->addInputComponent(MSC);
		gc2->setColFrame(shopObjects[i].colFrame); gc2->setRowFrame(shopObjects[i].FilFrame);

		stageBack(gc2); //A�adimos la imagen de detr�s del objeto al stage
		stageBack(gc); //A�adimos el objeto
		GCshopV.push_back(gc); //A�adimos el elemento al vector de Items de la tienda
		k++;
	}
}

void ShopState::createBagItems() {
	int k = 0;
	int j = 0;
	ocupados = 0;
	for (unsigned int i = 0; i < invent.size(); i++) {

		SP[i].ID = invent[i].ID;
		SP[i].objects++;
		SP[i].empty = false;
		SP[i].comprado = true;
		SP[i].price = invent[i].price;
		SP[i].tx = invent[i].tx;
		SP[i].type = invent[i].type;

		GameComponent* gc = new GameComponent(game);
		Vector2D position0(SP[i].y, SP[i].x);
		double width = 70;
		double height = 70;

		gc->setText(invent[i].tx); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
		gc->addRenderComponent(rcF); gc->addInputComponent(MSC);  gc->addInputComponent(new MouseInfoClickComponent(invent[i]));
		gc->setColFrame(invent[i].colFrame); gc->setRowFrame(invent[i].FilFrame);

		stage.push_back(gc);
		GCInventV.push_back(gc);

		ocupados++;

		k++;
	}
}

void ShopState::destroyMatix() {

	SP.clear();
}

void ShopState::createMatrix() {

	fillMatrix();

}

void ShopState::fillMatrix() {
	//Rellenamos la matriz DE SP
	Vector2D selecPos;
	int auxD = 0;
	auxOID = 0;
	numSP = 0;
	for (int i = 0; i < Cols; i++)
		for (int j = 0; j < Fils; j++) {
			estado a;


			double width = 70;
			double height = 70;
			a.empty = true;
			a.ID = 0;
			a.objects = 0;
			a.w = width;
			a.h = height;
			a.mX = i;
			a.mY = j;
			a.objectID = auxOID;
			a.type = -1;


			Vector2D position0(2 * i + 2, 2 * j + 2);
			if (i == 0 && j == 0)
				selecPos = position0;
			if (i == 1 && j == 0)
				auxD = position0.getX() - selecPos.getX();

			a.x = position0.getX();
			a.y = position0.getY();
			GameComponent* gc = new GameComponent(game);
			InputComponent* auxSCP = new MouseScrollShopComponent(this, auxOID);

			gc->setText(standPoint); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
			gc->addRenderComponent(rcF); gc->addInputComponent(auxSCP);//  gc->addInputComponent(InventoryShopFBcomponent());

			stage.push_back(gc);
			SP.push_back(a);
			StandPointsO.push_back(gc);

			numSP++;
			auxOID++;
		}
	ultimaFilaY = Fils;

	//Creamos el elemento que nos permitir� movernos con teclado
	selector_ = new GameComponent(game);

	selector_->setText(game->getTexture(12)); selector_->setPosition(selecPos);
	selector_->setWidth(70); selector_->setHeight(70);
	selector_->addRenderComponent(rcF); selector_->addInputComponent(new KeyBoardBackPackComponent(selecPos.getX(), selecPos.getY(), Fils, Cols, auxD, StandPointsO, nullptr, this));
	selector_->addInputComponent(MSC);

	stage.push_back(selector_);

	//Creamos los elementos de la mochila
	createBagItems();
}

bool ShopState::handleEvent(SDL_Event & event)
 {
	// 1) Comprueba las teclas de acceso a los distintos men�s, etc.
		if (event.type == SDL_KEYDOWN)
		 {
			if (event.key.keysym.sym == SDLK_ESCAPE)
				toMenu(game);
			}
		// 2) LLama a los input de cada objeto del propio estado
		return GameState::handleEvent(event);
	}