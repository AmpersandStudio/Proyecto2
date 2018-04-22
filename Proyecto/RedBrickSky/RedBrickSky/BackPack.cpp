#include "BackPack.h"
#include "DragNDropComponent.h"
#include "InventBottomsComponent.h"
#include "InventoryShopFBcomponent.h"
#include "RenderSingleFrameComponent.h"
#include "BagXboxControllerComponent.h"
#include "RenderFraemeComponent2.h"

BackPack::BackPack()
{
	money = GameManager::Instance()->getMoney();
	invent = GameManager::Instance()->copyInventory();
	cout << "Tam Inventario:  " << invent.size() << endl;

	//Componentes necesarios
	actualState_ = 0;

	//Creamos la matriz
	matriz = new estado*[numFils];
	for (int i = 0; i < numFils; i++) {
		matriz[i] = new estado[numRows];
	}
	
	if (XboxController::Instance()->getNumControllers() == 0) //SOLO UN MANDO
		XboxController::Instance()->insertController();

	separateElements();

	creaEscena();
}

BackPack::~BackPack()
{
	if (matriz != nullptr) {
		for (int i = 0; i < numFils; i++)
			if (matriz[i] != nullptr)
				delete[]matriz[i];
		delete[]matriz;
	}
	matriz = nullptr;

	//para borrar la basura de punteros que referencian a nada
	//he hecho un vector auxiliar que los guarda para borrarlos aqui
	for (int i = 0; i < auxGOforDeleting.size(); i++) {
		if (auxGOforDeleting[i] != 0) delete auxGOforDeleting[i];
	}
	auxGOforDeleting.clear();

	GameState::~GameState();
}

bool BackPack::handleEvent(const SDL_Event & event)
{
		// 1) Comprueba las teclas de acceso a los distintos menús, etc.
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				GameManager::Instance()->changeInventory(invent);
				toMenu();
			}
		}

		else if (event.type == SDL_JOYBUTTONDOWN) {

			XboxController::Instance()->onJoystickButtonDown(event);

			if (XboxController::Instance()->getButtonState(0, 6)) {
				GameManager::Instance()->changeInventory(invent);
				toMenu();
			}

			if (XboxController::Instance()->getButtonState(0, 1) && buttonsCreated) {//Si se ha pulsado la B
				GameManager::Instance()->changeInventory(invent);
				toMenu();
			}
			else if (XboxController::Instance()->getButtonState(0, 0) && buttonsCreated) {
				elimina();
				creaSP();
				cargaElementos(Weapons);
			}

			else if (XboxController::Instance()->getButtonState(0, 2) && buttonsCreated) {
				elimina();
				creaSP();
				cargaElementos(Potions);
			}

			else if (XboxController::Instance()->getButtonState(0, 3) && buttonsCreated) {
				elimina();
				creaSP();
				cargaElementos(Objects);
			}

			
		}

		else if (event.type == SDL_JOYBUTTONUP)
			XboxController::Instance()->onJoystickButtonUp(event);
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

		if (l[i].mX != -10 && l[i].mY != -10) {

			int x = l[i].mX;
			int y = l[i].mY;
			createItemAtSP(x, y, l[i].objectID, l[i]);

			bool found = false;
			for (int i = 0; i < SP.size() && !found; i++) {
				if (SP[i].mX == x && SP[i].mY == y) {
					found = true;
					SP[i].empty = false;
				}
			}
		}
		else
			auxV.push_back(l[i]);
	}

	//todos aquellos elementos que no hayan sido ordenados previamente, los asignamos a un lugar 

	for (int p = 0; p < auxV.size(); p++)
	{
		int aux = 0;
		int i = 0;
		int j = 0;
		bool place = false;
		while (i < numFils && !place) {
			if (j > numRows) {
				i++;
				j = 0;
			}

			if (SP[aux].empty == true) {
				int x = SP[aux].mX;
				int y = SP[aux].mY;
				createItemAtSP(x, y, auxV[p].objectID, auxV[p]);
				SP[aux].empty = false;
				auxV[p].mX = x;
				auxV[p].mY = y;
				auxV[p].GC = invent[auxV[p].objectID].GC;
				place = true;
			}
			else {
				j++;
				aux++;
			}
		}
	}

	vector<estado> auxSP = SP;
	setSP(auxSP);

	if (auxV.size() != 0) {
		invent.clear();
		bool armas = auxV[0].type == 0;
		bool pociones = auxV[0].type == 1;
		bool objetos = auxV[0].type == 2;

		if (!armas) { //armas

			for (int i = 0; i < Weapons.size(); i++)
				invent.push_back(Weapons[i]);
		}

		else if (!pociones) { //Pociones
			for (int i = 0; i < Potions.size(); i++)
				invent.push_back(Potions[i]);
		}

		else if (!objetos) { //Objetos
			for (int i = 0; i < Objects.size(); i++)
				invent.push_back(Objects[i]);
		}

		for (int i = 0; i < auxV.size(); i++)
			invent.push_back(auxV[i]);

		separateElements();
	}
}

void BackPack::createItemAtSP(int x, int y, int aux, estado st) {

	matriz[x][y].ID = st.ID;
	matriz[x][y].objects++;
	matriz[x][y].empty = false;
	matriz[x][y].comprado = true;
	matriz[x][y].price = st.price;
	matriz[x][y].tx = st.tx;
	matriz[x][y].w = st.w;
	matriz[x][y].h = st.h;
	matriz[x][y].objectID = aux;
	st.mX = matriz[x][y].mX;
	st.mY = matriz[x][y].mY;
	st.x = matriz[x][y].x;
	st.y = matriz[x][y].y;

	matriz[x][y].colFrame = st.colFrame;
	matriz[x][y].FilFrame = st.FilFrame;

	GameComponent* gc = new GameComponent();
	Vector2D position0(st.x, st.y);

	gc->setTextureId(matriz[x][y].tx); gc->setPosition(position0); gc->setWidth(matriz[x][y].w); gc->setHeight(matriz[x][y].h);
	gc->addRenderComponent(new RenderSingleFrameComponent()); gc->addInputComponent(new MouseInfoClickComponent(st)); gc->addInputComponent(new DragNDropComponent(this, aux));
	gc->setOriPos(position0);
	gc->setColFrame(matriz[x][y].colFrame); gc->setRowFrame(matriz[x][y].FilFrame);
	
	st.GC = gc;

	invent[aux].GC = gc;
	stage.push_back(gc);
}

void BackPack::creaSP() {
	player->setActive(false);
	
	buttonsCreated = false;

	//Creamos los SP
	Vector2D selecPos;
	int auxD = 0;
	int aux = 0;
	
	//StandPoints para guardar los objetos en el inventario
	for (int i = 0; i < numFils; i++)
		for (int j = 0; j < numRows; j++) {

			double width = 50;
			double height = 50;
			matriz[i][j].empty = true;
			matriz[i][j].ID = 0;
			matriz[i][j].objects = 0;
			matriz[i][j].w = width;
			matriz[i][j].h = height;
			matriz[i][j].mX = i;
			matriz[i][j].mY = j;

			Vector2D position0(2 * i + 9.5, 2 * j + 3);
			if (i == 0 && j == 0)
				selecPos = position0;
			if (i == 0 && j == 1)
				auxD = position0.getY() - selecPos.getY();

			matriz[i][j].x = position0.getX();
			matriz[i][j].y = position0.getY();
			GameComponent* gc = new GameComponent();

			gc->setTextureId("8"); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
			gc->addRenderComponent(new RenderSingleFrameComponent()); //gc->addInputComponent(mooCP); //gc->addInputComponent(auxSCP);

			stage.push_back(gc);
			SP.push_back(matriz[i][j]); 
			StandPointsO.push_back(gc);
			numSP++;
			aux++;
		}

	ultimaFilaY = 4;
	actFilas = 1;

	//StandPoints para EQUIPAR los objetos al personaje
	int auxP = 1;
	for (int i = 0; i < 2; i++) {

		estado s;
		int width = 70;
		int height = 70;
		s.empty = true;
		s.ID = 0;
		s.objects = 0;
		s.w = width;
		s.h = height;
		auxP++;
		s.equiped = true;
		s.mX = 0;
		s.mY = (i + 1) * -1;

		Vector2D position0(2 * i + 1.5, 6);

		s.x = position0.getX();
		s.y = position0.getY();
		GameComponent* gc = new GameComponent();

		gc->setTextureId("8"); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
		gc->addRenderComponent(new RenderSingleFrameComponent()); //gc->addInputComponent(mooCP); //gc->addInputComponent(auxSCP);

		stage.push_back(gc);
		SP.push_back(s);
		StandPointsO.push_back(gc);

		if(EItems > 0){
			EItems--;
			EquipedItems[EItems].x = position0.getX();
			EquipedItems[EItems].y = position0.getY();

		}
	}

	//Ponemos los objetos que tenga el personaje
	
	for (int x = 0; x < EquipedItems.size(); x++) {
		GameComponent* gc = new GameComponent();
		if (x == 0) {
			Vector2D position0(EquipedItems[x].x + 0.8, EquipedItems[x].y + 2.6);
			gc->setPosition(position0);
			gc->setOriPos(position0);
		}
		else {
			Vector2D position1(EquipedItems[x].x + 1.1, EquipedItems[x].y + 2.6);
			gc->setPosition(position1);
			gc->setOriPos(position1);
		}

		gc->setTextureId(EquipedItems[x].tx);  gc->setWidth(EquipedItems[x].w); gc->setHeight(EquipedItems[x].h);
		gc->addRenderComponent(new RenderSingleFrameComponent()); //gc->addInputComponent(new MouseInfoClickComponent(st)); 

		gc->setColFrame(EquipedItems[x].colFrame); gc->setRowFrame(EquipedItems[x].FilFrame);
	
		if(actualState_ == 0)
			gc->addInputComponent(new DragNDropComponent(this, x * -1));

		EquipedItems[x].GC = gc;

		//invent[aux].GC = gc;
		stage.push_back(gc);

	}

	//Creacion del botón que nos devolverá a los anteriores
	GameComponent* weapon = new GameComponent();

	Vector2D positionW(5, 0.5);

	weapon->setTextureId("2"); weapon->setPosition(positionW); weapon->setWidth(120); weapon->setHeight(60);
	weapon->addRenderComponent(new RenderSingleFrameComponent());  weapon->addInputComponent(new InventBottomsComponent(this, Weapons, true, 0));

	stage.push_back(weapon);
	botones.push_back(weapon);

	//Creamos el elemento que nos permitirá movernos con teclado
	selector_ = new GameComponent();

	selector_->setTextureId("12"); selector_->setPosition(selecPos);
	selector_->setWidth(50); selector_->setHeight(50);
	selector_->setColFrame(0); selector_->setRowFrame(0);
	selector_->addRenderComponent(new RenderSingleFrameComponent()); selector_->addInputComponent(new KeyBoardBackPackComponent(selecPos.getX(), selecPos.getY(), numRows - 1, numFils, auxD, StandPointsO, this));
	selector_->addInputComponent(new BagXboxControllerComponent(selecPos.getX(), selecPos.getY(), numRows - 1, numFils, auxD, StandPointsO, this));
	//selector_->addInputComponent(MSC);
	stage.push_back(selector_);

	GameManager::Instance()->changeInventory(invent);
}

void BackPack::elimina() {

	for (int i = 0; i < stage.size(); i++) {
		GameObject* aux = *(stage.begin() + i);
		if (aux != nullptr) {
			auxGOforDeleting.push_back(aux);
		}
		stage.erase(stage.begin() + i);
		i--;
	}

	SP.clear();
	botones.clear();

	creaFondoTienda();
}

void BackPack::creaEscena() {
	
	invent.clear();
	invent = GameManager::Instance()->copyInventory();
	separateElements();

	creaFondoTienda();

	//Creamos botón para volver al menú principal y los de cada clase
	Button* bottonBack = new Button("3", toMenu, 0);

	Vector2D position0(5, 0.5);

	double width = 120;
	double height = 60;

	bottonBack->setTextureId("3"); bottonBack->setPosition(position0); bottonBack->setWidth(width); bottonBack->setHeight(height);
	bottonBack->addRenderComponent(new RenderSingleFrameComponent()); bottonBack->addInputComponent(new MouseScrollComponent());

	stage.push_back(bottonBack);

	//Creacion de los "botones" que nos llevarán a cada tipo de Item del inventario
	//Boton para las armas
	createButtons(4, 3, Weapons, "14", 0);

	//Boton para las pociones
	createButtons(4, 5, Potions, "15", 1);

	//Boton para los objetos
	createButtons(4, 7, Objects, "16",2);	
}

void BackPack::creaFondoTienda() {

	//Imagen de fondo de la tienda
	GameComponent* backShop = new GameComponent();
	backShop->setTextureId("9"); backShop->addRenderComponent(new RenderFullComponent());
	stage.push_back(backShop);

	player = new BattlePlayer("Tyler", Physical, 1000, 10, 10, 100, 10);
	player->setTextureId("tylerSS");
	Vector2D pos(0.35, 0.12);
	player->setPosition(pos);
	player->setWidth(256); player->setHeight(512);
	player->setRowFrame(0); player->setColFrame(0);
	RenderComponent* rc = new RenderFraemeComponent2();
	player->addRenderComponent(rc);
	stage.push_back(player);
}

void BackPack::createButtons(int x, int y, vector<estado> type, std::string t, int st) {

	GameComponent* GC = new GameComponent();

	Vector2D position(x, y);

	GC->setTextureId(t); GC->setPosition(position); GC->setWidth(130); GC->setHeight(60);
	GC->addRenderComponent(new RenderSingleFrameComponent());  GC->addInputComponent(new InventBottomsComponent(this, type, false, st));

	stage.push_back(GC);
	botones.push_back(GC);

	buttonsCreated = true;

}

void BackPack::setInvent(vector<estado> v) {
	invent.clear();
	for (int i = 0; i < v.size(); i++)
		invent.push_back(v[i]);

	separateElements();
}

void BackPack::setSP(vector<estado> v) {
	SP.clear();
	for (int i = 0; i < v.size(); i++)
		SP.push_back(v[i]);
}

void BackPack::separateElements() {
	//Guardamos los elementos del inventario en sus correspondientes vectores
	Weapons.clear();
	Potions.clear();
	Objects.clear();
	EquipedItems.clear();
	EItems = 0;
	for (unsigned int i = 0; i < invent.size(); i++) {
		invent[i].objectID = i;
		if (invent[i].equiped == false) {
			if (invent[i].type == 0)
				Weapons.push_back(invent[i]);
			else if (invent[i].type == 1)
				Potions.push_back(invent[i]);
			else if (invent[i].type == 2)
				Objects.push_back(invent[i]);
		}
		else {
			EquipedItems.push_back(invent[i]);
			EItems++;
		}
	}
}

void BackPack::update() {
	player->setColFrame(int(((SDL_GetTicks() / (200)) % 4)));
	GameState::update();
}