#include "BackPack.h"
#include "DragNDropComponent.h"
#include "InventoryShopFBcomponent.h"
#include "RenderSingleFrameComponent.h"
#include "BagXboxControllerComponent.h"
#include "KeyInputComponentButton.h"
#include "MouseInputForBattleComponent.h"
#include "RenderFraemeComponent2.h"
#include "ClickButtonComp.h"

BackPack::BackPack()
{

	TheSoundManager::Instance()->playSound("cremallera", 0);
	money = GameManager::Instance()->getMoney();
	invent.clear();
	invent = GameManager::Instance()->copyInventory();
	std::cout << invent.size() << endl;

	StringToScreen::Instance()->pushInfinite(std::to_string(GameManager::Instance()->getMoney()), 130, 515);
	StringToScreen::Instance()->pushInfinite(std::to_string(GameManager::Instance()->getPotions()), 280, 495);

	//Componentes necesarios
	actualState_ = 0;
	SDL_ShowCursor(1);
	//Creamos la matriz
	matriz = new estado*[numFils];
	for (int i = 0; i < numFils; i++) {
		matriz[i] = new estado[numRows];
	}

	if (XboxController::Instance()->getNumControllers() == 0) //SOLO UN MANDO
		XboxController::Instance()->insertController();

	Vector2D v(0.35, 0.12);
	Vector2D v2(0.75, 0.3);
	pos1 = v; pos2 = v2;
	width1 = 256; width2 = 171;
	height1 = 512; height2 = 341;
	EItems = 0;
	leftOccupied = false;
	creaEscena();

	Button* button0 = new Button("clb", cleonMode, 0);
	Vector2D position0(0.05, 0.8);
	double width = 180;
	double height = 45;
	button0->setPosition(position0); button0->setWidth(width); button0->setHeight(height); button0->addRenderComponent(new RenderFrameComponent());
	button0->addInputComponent(new ClickButtonComp());
	stage.push_back(button0);
}

BackPack::~BackPack()
{

	SDL_ShowCursor(0);
	StringToScreen::Instance()->clearInfinite();
	StringToScreen::Instance()->stopRendering();
	GameManager::Instance()->changeInventory(invent);

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
			toMenu();
		}
	}

	else if (event.type == SDL_JOYBUTTONDOWN) {

		XboxController::Instance()->onJoystickButtonDown(event);

		if (XboxController::Instance()->getButtonState(0, 6)) {
			toMenu();
		}

		if (XboxController::Instance()->getButtonState(0, 1) && buttonsCreated) {//Si se ha pulsado la B
			toMenu();
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

void BackPack::cargaElementos() {

	//Asginamos los elementos dentro del vector de la mochila a cada casilla
	int auxP = 0;
	for (unsigned int i = 0; i < invent.size(); i++) {

		if (!invent[i].equiped) {

			invent[i].objectID = auxP;

			int aux = 0;
			int h = 0;
			int j = 0;
			bool place = false;
			while (h < numFils && !place) {
				if (j > numRows) {
					h++;
					j = 0;
				}

				if (SP[aux].empty == true) {
					int x = SP[aux].mX;
					int y = SP[aux].mY;
					createItemAtSP(x, y, invent[i].objectID, invent[i]);
					SP[aux].empty = false;
					invent[i].mX = x;
					invent[i].mY = y;
					invent[i].GC = invent[invent[i].objectID].GC;
					place = true;
				}
				else {
					j++;
					aux++;
				}
			}
		}
		auxP++;
	}
	vector<estado> stand = SP;
	setSP(stand);

	//Ponemos los objetos que tenga el personaje

	for (int x = 0; x < EquipedItems.size(); x++) {


		GameComponent* gc = new GameComponent();
		if (x == 0) {
			Vector2D position0(2.6, 9.7);
			gc->setPosition(position0);
			gc->setOriPos(position0);
			leftOccupied = true;
		}
		else {
			Vector2D position1(5.8, 9.7);
			gc->setPosition(position1);
			gc->setOriPos(position1);
		}

		gc->setTextureId(EquipedItems[x].tx);  gc->setWidth(EquipedItems[x].w); gc->setHeight(EquipedItems[x].h);
		gc->addRenderComponent(new RenderSingleFrameComponent());

		gc->setColFrame(EquipedItems[x].colFrame); gc->setRowFrame(EquipedItems[x].FilFrame);

		if (actualState_ == 0)
			gc->addInputComponent(new DragNDropComponent(this, x)); //AQUI ESTA EL CAMBIO 

		

		EquipedItems[x].GC = gc;

		stage.push_back(gc);
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
	gc->addRenderComponent(new RenderSingleFrameComponent());  gc->addInputComponent(new DragNDropComponent(this, aux));
	gc->setOriPos(position0);
	gc->setColFrame(matriz[x][y].colFrame); gc->setRowFrame(matriz[x][y].FilFrame);

	st.GC = gc;

	invent[aux].GC = gc;
	stage.push_back(gc);
}

void BackPack::creaSP() {

	for (int i = 0; i < invent.size(); i++) {
		
		if (invent[i].equiped) {
			EItems++;
			EquipedItems.push_back(invent[i]);
		}
	}

	buttonsCreated = false;

	player->setPosition(pos2);
	player->setWidth(width2);
	player->setHeight(height2);

	//Creamos los SP
	Vector2D selecPos;
	int auxD = 0;
	int aux = 0;

	//StandPoints para guardar los objetos en el inventario
	for (int i = 0; i < numFils; i++)
		for (int j = 0; j < numRows; j++) {

			double width = 45;
			double height = 45;
			matriz[i][j].empty = true;
			matriz[i][j].ID = aux;
			matriz[i][j].objects = 0;
			matriz[i][j].w = width;
			matriz[i][j].h = height;
			matriz[i][j].mX = i;
			matriz[i][j].mY = j;

			Vector2D position0(1.7 * i + 11, 1.7 * j + 2.8);
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
		StandPointsO.push_back(gc);
	}

	//Creamos el elemento que nos permitirá movernos con teclado
	selector_ = new GameComponent();

	selector_->setTextureId("12"); selector_->setPosition(selecPos);
	selector_->setWidth(45); selector_->setHeight(45);
	selector_->setColFrame(0); selector_->setRowFrame(0);
	selector_->addRenderComponent(new RenderSingleFrameComponent()); selector_->addInputComponent(new KeyBoardBackPackComponent(selecPos.getX(), selecPos.getY(), numRows - 1, numFils, auxD, StandPointsO, this));
	selector_->addInputComponent(new BagXboxControllerComponent(selecPos.getX(), selecPos.getY(), numRows - 1, numFils, auxD, StandPointsO, this));
	//selector_->addInputComponent(MSC);
	stage.push_back(selector_);
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


	creaFondoTienda();

	//Creamos botón para volver al menú principal y los de cada clase
	Button* bottonBack = new Button("3", toMenu, 0);

	Vector2D position0(5.25, 0.5);

	double width = 120;
	double height = 60;

	bottonBack->setTextureId("3"); bottonBack->setPosition(position0); bottonBack->setWidth(width); bottonBack->setHeight(height);
	bottonBack->addRenderComponent(new RenderSingleFrameComponent());// bottonBack->addInputComponent(new MouseScrollComponent());
	bottonBack->addInputComponent(new MouseInputComponentButton());

	stage.push_back(bottonBack);

	creaSP();
	cargaElementos();
}

void BackPack::creaFondoTienda() {

	//Imagen de fondo de la tienda
	GameComponent* backShop = new GameComponent();
	backShop->setTextureId("9"); backShop->addRenderComponent(new RenderFullComponent());
	stage.push_back(backShop);

	player = new BattlePlayer("Tyler", Physical, 1000, 10, 10, 100, 10);
	player->setTextureId("tylerSS");
	player->setPosition(pos1);
	player->setWidth(width1); player->setHeight(height1);
	player->setRowFrame(0); player->setColFrame(0);
	RenderComponent* rc = new RenderFraemeComponent2();
	player->addRenderComponent(rc);
	stage.push_back(player);
}

void BackPack::createButtons(int x, int y, vector<estado> type, std::string t, int st) {

	GameComponent* GC = new GameComponent();

	Vector2D position(x, y);

	GC->setTextureId(t); GC->setPosition(position); GC->setWidth(130); GC->setHeight(60);
	GC->addRenderComponent(new RenderSingleFrameComponent());

	stage.push_back(GC);
	botones.push_back(GC);

	buttonsCreated = true;
}

void BackPack::setInvent(vector<estado> v) {
	invent.clear();
	for (int i = 0; i < v.size(); i++)
		invent.push_back(v[i]);
}

void BackPack::setSP(vector<estado> v) {
	SP.clear();
	for (int i = 0; i < v.size(); i++)
		SP.push_back(v[i]);
}

void BackPack::update() {
	player->setColFrame(int(((SDL_GetTicks() / (200)) % 4)));
	GameState::update();
}

void BackPack::render() {

	GameState::render();

	//BARRA DE VIDA

	TheTextureManager::Instance()->drawFull("inventHP", 142, 122,
		180, 30, Game::Instance()->getRenderer(), 0, 255);

	Vector2D position0(172, 138);

	int iniwidth = 120;
	int height = 8;

	int width = (GameManager::Instance()->getHealth() < GameManager::Instance()->getMaxHealth()) ? (GameManager::Instance()->getHealth() * iniwidth / GameManager::Instance()->getMaxHealth()) : iniwidth;
	if (width < 0) width = 0;

	SDL_Rect fillRect = { (int)position0.getX(), (int)position0.getY() , width, height };
	if (width > iniwidth / 2)
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
	else if (width > iniwidth / 3)
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0xFF, 0xFF, 0x00, 0xFF);
	else
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(Game::Instance()->getRenderer(), &fillRect);


	//Sweeties
	TheTextureManager::Instance()->drawItem("sweet", 90, 510,
		50, 30, 0, 0, 1, 2, Game::Instance()->getRenderer(), 0, 255);
	//Potions
	TheTextureManager::Instance()->drawItem("21", 260, 510,
		32, 32, 4, 0, 8, 8, Game::Instance()->getRenderer(), 0, 255);


}