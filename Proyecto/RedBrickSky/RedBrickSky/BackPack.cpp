#include "BackPack.h"
#include "DragNDropComponent.h"
#include "InventBottomsComponent.h"
#include "InventoryShopFBcomponent.h"
#include "RenderSingleFrameComponent.h"

BackPack::BackPack()
{
	invent = GameManager::Instance()->copyInventory();
	money = GameManager::Instance()->getMoney();
	cout << invent.size() << endl;

	//Componentes necesarios
	rcF = new RenderSingleFrameComponent(); //Render Frame
	rc = new RenderFullComponent(); //Render FS
	rcSF = new RenderSingleFrameComponent();
	//MSC = new MouseScrollComponent();
	//MSOC = new MouseOverObjectComponent();
	MIC = new MouseInputComponentButton();
	//DND = new DragNDropComponent(this); //this es el puntero a tienda
	//Info = new MouseInfoClickComponent();

	//Creamos la matriz
	matriz = new estado*[numFils];
	for (int i = 0; i < numFils; i++) {
		matriz[i] = new estado[numRows];
	}
	
	separateElements();

	creaEscena();
}

BackPack::~BackPack()
{
}

bool BackPack::handleEvent(const SDL_Event & event)
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

void BackPack::toMenu() {
	
	StateMachine* sm = Game::Instance()->getStateMachine();
	sm->popState();
}

void BackPack::cargaElementos(vector<estado> l) {

	//Asginamos los elementos dentro del vector de la mochila a cada casilla
	vector<estado> auxV;
	for (unsigned int i = 0; i < l.size(); i++) {

		if (l[i].mX != -1 && l[i].mY != -1) {

			int x = l[i].mX;
			int y = l[i].mY;
			createItemAtSP(x, y, l[i].objectID, l[i]);
		}

		else	
			auxV.push_back(l[i]);
	}

	//todos aquellos elementos que no hayan sido ordenados previamente, los asignamos a un lugar 
	for (int p = 0; p < auxV.size(); p++)
	{
		int i = 0;
		int j = 0;
		bool place = false;
		while (i < numFils && !place) {
			if (j > numRows) {
				i++;
				j = 0;
			}

			if (matriz[i][j].empty == true) {
				int x = j;
				int y = i;
				createItemAtSP(x, y, auxV[p].objectID, auxV[p]);
				place = true;
				matriz[i][j].empty == false;
			}
			else 
				j++;
		}
	}
}

void BackPack::createItemAtSP(int x, int y, int aux, estado st) {

	matriz[x][y].ID = st.ID;
	matriz[x][y].objects++;
	matriz[x][y].empty = false;
	matriz[x][y].comprado = true;
	matriz[x][y].price = st.price;
	matriz[x][y].tx = st.tx;
	matriz[x][y].w = 70;
	matriz[x][y].h = 70;
	matriz[x][y].objectID = aux;
	st.mX = matriz[x][y].mX;
	st.mY = matriz[x][y].mY;
	matriz[x][y].colFrame = st.colFrame;
	matriz[x][y].FilFrame = st.FilFrame;

	GameComponent* gc = new GameComponent();
	Vector2D position0(matriz[x][y].x, matriz[x][y].y);

	gc->setTextureId(matriz[x][y].tx); gc->setPosition(position0); gc->setWidth(matriz[x][y].w); gc->setHeight(matriz[x][y].h);
	gc->addRenderComponent(rcSF); gc->addInputComponent(new MouseInfoClickComponent(st)); gc->addInputComponent(new DragNDropComponent(this, aux));
	gc->setOriPos(position0);
	gc->setColFrame(matriz[x][y].colFrame); gc->setRowFrame(matriz[x][y].FilFrame);

	invent[aux].GC = gc;
	stage.push_back(gc);
}

void BackPack::creaSP() {
	//Creamos los SP
	Vector2D selecPos;
	int auxD = 0;
	int aux = 0;
	
	for (int i = 0; i < numFils; i++)
		for (int j = 0; j < numRows; j++) {

			estado s;
			double width = 70;
			double height = 70;
			matriz[i][j].empty = true;
			matriz[i][j].ID = 0;
			matriz[i][j].objects = 0;
			matriz[i][j].w = width;
			matriz[i][j].h = height;
			matriz[i][j].mX = i;
			matriz[i][j].mY = j;


			Vector2D position0(2 * i + 11, 2 * j + 2);
			if (i == 0 && j == 0)
				selecPos = position0;
			if (i == 0 && j == 1)
				auxD = position0.getY() - selecPos.getY();

			matriz[i][j].x = position0.getX();
			matriz[i][j].y = position0.getY();
			GameComponent* gc = new GameComponent();
			//InputComponent* auxSCP = new MouseScrollComponent();
			//InputComponent* mooCP = new MouseOverObjectComponent();

			gc->setTextureId("8"); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
			gc->addRenderComponent(rcF); //gc->addInputComponent(mooCP); //gc->addInputComponent(auxSCP);

			stage.push_back(gc);
			SP.push_back(matriz[i][j]);
			StandPointsO.push_back(gc);
			numSP++;
			aux++;
		}
	ultimaFilaY = 4;
	actFilas = 1;

	//Creacion del bot�n que nos devolver� a los anteriores
	GameComponent* weapon = new GameComponent();

	Vector2D positionW(7, 6);

	weapon->setTextureId("2"); weapon->setPosition(positionW); weapon->setWidth(150); weapon->setHeight(100);
	weapon->addRenderComponent(rcF);  weapon->addInputComponent(new InventBottomsComponent(this, Weapons, true));

	stage.push_back(weapon);
	botones.push_back(weapon);

	//Creamos el elemento que nos permitir� movernos con teclado
	selector_ = new GameComponent();

	selector_->setTextureId("12"); selector_->setPosition(selecPos);
	selector_->setWidth(70); selector_->setHeight(70);
	selector_->addRenderComponent(rcF); selector_->addInputComponent(new KeyBoardBackPackComponent(selecPos.getX(), selecPos.getY(), numRows, numFils, auxD, StandPointsO, this));
	//selector_->addInputComponent(MSC);
	stage.push_back(selector_);
}

void BackPack::elimina() {

	for (int i = 0; i < stage.size(); i++) {

			stage.erase(stage.begin() + i);
			i--;
	}

	SP.clear();
	botones.clear();

	creaFondoTienda();
}

void BackPack::creaEscena() {
	
	creaFondoTienda();

	//Creamos bot�n para volver al men� principal y los de cada clase
	Button* bottonBack = new Button("3", toMenu, 0);

	Vector2D position0(7, 0);

	double width = 150;
	double height = 100;

	bottonBack->setTextureId("3"); bottonBack->setPosition(position0); bottonBack->setWidth(width); bottonBack->setHeight(height);
	bottonBack->addRenderComponent(rcF); bottonBack->addInputComponent(MIC);

	stage.push_back(bottonBack);

	//Creacion de los "botones" que nos llevar�n a cada tipo de Item del inventario
	//Boton para las armas
	createButtons(6, 2, Weapons, "14");

	//Boton para las pociones
	createButtons(6, 4, Potions, "15");


	//Boton para los objetos
	createButtons(6, 6, Objects, "16");

	GameManager::Instance()->changeInventory(invent);
}

void BackPack::creaFondoTienda() {

	//Imagen de fondo de la tienda
	GameComponent* backShop = new GameComponent();
	backShop->setTextureId("9"); backShop->addRenderComponent(rc);
	stage.push_back(backShop);
}

void BackPack::createButtons(int x, int y, vector<estado> type, std::string t) {

	GameComponent* GC = new GameComponent();

	Vector2D position(x, y);

	GC->setTextureId(t); GC->setPosition(position); GC->setWidth(150); GC->setHeight(100);
	GC->addRenderComponent(rcF);  GC->addInputComponent(new InventBottomsComponent(this, type, false));

	stage.push_back(GC);
	botones.push_back(GC);

}

void BackPack::setInvent(vector<estado> v) {
	invent.clear();
	for (int i = 0; i < v.size(); i++)
		invent.push_back(v[i]);

	separateElements();
}

void BackPack::separateElements() {
	//Guardamos los elementos del inventario en sus correspondientes vectores
	Weapons.clear();
	Potions.clear();
	Objects.clear();
	for (unsigned int i = 0; i < invent.size(); i++) {
		invent[i].objectID = i;
		if (invent[i].type == 0)
			Weapons.push_back(invent[i]);
		else if (invent[i].type == 1)
			Potions.push_back(invent[i]);
		else if (invent[i].type == 2)
			Objects.push_back(invent[i]);

		//ocupados++;
	}
}
