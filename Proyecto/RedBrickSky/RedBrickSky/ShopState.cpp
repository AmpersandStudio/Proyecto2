#pragma once

#include "ShopState.h"
#include "Button.h"
#include <iostream>


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
	bot = gamePtr->getTexture(3); //Para el botón
	

	//Componentes necesarios
	rcF = new RenderFrameComponent(); //Render Frame
	rc = new RenderFullComponent(); //Render FS
	MSC = new MouseScrollShopComponent(this);
	MSOC = new MouseOverObjectComponent();
	MIC = new MouseInputComponentButton();

	//Separamos elementos dependiendo de su clase
	separateElements();

	//Imagen de fondo de la tienda
	GameComponent* backShop = new GameComponent(game);
	backShop->setText(back); backShop->addRenderComponent(rc);
	stage.push_back(backShop);

	//Creamos la matiz y la llenamos de StandPoints
	createMatrix();

	//Creación de los items que tendrá la tienda
	createShopItems();

	//Creamos la imagen que va por encima de la mochila para que no se vea al hacer scroll
	GameComponent* frontShop = new GameComponent(game);
	frontShop->setText(front); frontShop->addRenderComponent(rc);
	stage.push_back(frontShop);

	//Creamos botón para volver al menú principal
	mainMenuBotton();

}

void ShopState::creaFila() {

	Fils++;
	//destroyMatix();
	createMatrix();
	ultimaFilaY += 2;
	
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
		DragNDropShopComponent* p = new DragNDropShopComponent(this, shopObjects[i].price, false, shopObjects[i].ID, gc, shopObjects[i].type, shopObjects[i].nombre);
		gc->setText(shopObjects[i].tx); gc->setOriPos(oriPos); gc->setPosition(position5); gc->setWidth(70); gc->setHeight(70);
		gc->addRenderComponent(rcF); gc->addInputComponent(p); gc->addInputComponent(new MouseInfoClickComponent(shopObjects[i]));	gc->addInputComponent(MSC);

		//Crea objetos debajo de los anteriores que no se moverán, serán solo imagen
		GameComponent* gc2 = new GameComponent(game);
		gc2->setText(shopObjects[i].tx); gc2->setOriPos(oriPos); gc2->setPosition(position5); gc2->setWidth(70); gc2->setHeight(70);
		gc2->addRenderComponent(rcF); gc2->addInputComponent(MSC);

		stageBack(gc2); //Añadimos la imagen de detrás del objeto al stage
		stageBack(gc); //Añadimos el objeto
		GCshopV.push_back(gc); //Añadimos el elemento al vector de Items de la tienda
		k++;
	}
}

void ShopState::createBagItems() {
	int k = 0;
	int j = 0;
	ocupados = 0;
	for (unsigned int i = 0; i < invent.size(); i++) {

		if (i % 3 == 0) {
			j++;
			k = 0;
		}

		matriz[j][k].ID = invent[i].ID;
		matriz[j][k].objects++;
		matriz[j][k].empty = false;
		matriz[j][k].comprado = true;
		matriz[j][k].price = invent[i].price;
		matriz[j][k].tx = invent[i].tx;
		matriz[j][k].type = invent[i].type;

		GameComponent* gc = new GameComponent(game);
		Vector2D position0(SP[i].x, SP[i].y);
		double width = 70;
		double height = 70;

		gc->setText(invent[i].tx); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
		gc->addRenderComponent(rcF); gc->addInputComponent(MSC);  gc->addInputComponent(new MouseInfoClickComponent(invent[i]));

		stage.push_back(gc);
		GCInventV.push_back(gc);

		ocupados++;
		cout << "Ocupados: " << ocupados << endl << "SP: " << numSP << endl;
		if (ocupados == numSP - 1)
			creaFila();
		
		k++;
	}
}

void ShopState::destroyMatix() {

	for(int i = 0; i < Cols; i++)
		if(matriz[i])
			delete matriz[i];
	delete matriz;
	SP.clear();
}

void ShopState::createMatrix() {

	//Creamos la matriz
	matriz = new estado*[Cols];
	for (int i = 0; i < Cols; i++) {
		matriz[i] = new estado[Fils];
	}

	fillMatrix();

}

void ShopState::fillMatrix() {
	//Rellenamos la matriz DE SP
	auxOID = 0;
	numSP = 0;
	for (int i = 0; i < Cols; i++)
		for (int j = 0; j < Fils; j++) {
			double width = 70;
			double height = 70;
			matriz[i][j].empty = true;
			matriz[i][j].ID = 0;
			matriz[i][j].objects = 0;
			matriz[i][j].w = width;
			matriz[i][j].h = height;
			matriz[i][j].mX = i;
			matriz[i][j].mY = j;
			matriz[i][j].objectID = auxOID;
			matriz[i][j].type = -1;

			//cout << matriz[i][j].mX << "," << matriz[i][j].mY << "," << endl;

			Vector2D position0(2 * i + 2, 2 * j + 2);
			matriz[i][j].x = position0.getX();
			matriz[i][j].y = position0.getY();
			GameComponent* gc = new GameComponent(game);
			InputComponent* auxSCP = new MouseScrollShopComponent(this, auxOID);

			gc->setText(standPoint); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
			gc->addRenderComponent(rcF); gc->addInputComponent(auxSCP);  gc->addInputComponent(MSOC);

			stage.push_back(gc);
			SP.push_back(matriz[i][j]);
			numSP++;
			auxOID++;
		}
	ultimaFilaY = Fils;

	//Creamos los elementos de la mochila
	createBagItems();
}

bool ShopState::handleEvent(SDL_Event & event)
 {
	// 1) Comprueba las teclas de acceso a los distintos menús, etc.
		if (event.type == SDL_KEYDOWN)
		 {
			if (event.key.keysym.sym == SDLK_ESCAPE)
				toMenu(game);
			}
		// 2) LLama a los input de cada objeto del propio estado
		return GameState::handleEvent(event);
	}
