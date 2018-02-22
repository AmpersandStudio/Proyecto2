#include "ShopState.h"
#include "Button.h"
#include "GameComponent.h"


ShopState::ShopState(Game* gamePtr) : GameState(gamePtr)
{
	game = gamePtr;


	invent = GameManager::Instance()->copyInventory();
	money = GameManager::Instance()->getMoney();
	std::cout << "Tu dinero actual es: " << money << std::endl;

	//Texturas necesitadas
	back = gamePtr->getTexture(6);
	standPoint = gamePtr->getTexture(8);
	front = gamePtr->getTexture(7);
	bot = gamePtr->getTexture(3); //Para el botón
	food = gamePtr->getTexture(4); //Para el botón

	//Componentes necesarios
	rcF = new RenderFrameComponent(); //Render Frame
	rc = new RenderFullComponent(); //Render FS
	MSC = new MouseScrollComponent();
	MSOC = new MouseOverObjectComponent();
	MIC = new MouseInputComponentButton();


	//Imagen de fondo de la tienda
	GameComponent* backShop = new GameComponent(game);
	backShop->setText(back); backShop->addRenderComponent(rc);
	stage.push_back(backShop);

	//Creamos la matriz
	matriz = new estado*[3];
	for (int i = 0; i < 3; i++) {
		matriz[i] = new estado[2];
	}
	//La rellenamos
	//tenemos en cuenta que estos son los StanPoints que se encuentran en la mochila dentro de la tienda. Los que están
	//en la tienda como tal son diferentes, ya que los elementos de la tienda son fijos
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++) {
			matriz[i][j].empty = true;
			matriz[i][j].ID = 0;
			matriz[i][j].objects = 0;
			
			GameComponent* gc = new GameComponent(game);
			Vector2D position0(2 * i +2, 2 * j + 2);
			double width = 70;
			double height = 70;

			gc->setText(standPoint); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
			gc->addRenderComponent(rcF); gc->addInputComponent(MSC);  gc->addInputComponent(MSOC);

			stage.push_back(gc);
			numSP++;
		}
	ultimaFilaY = 4;
	actFilas = 1;

	//Asginamos los elementos dentro del vector de la mochila a cada casilla
	for (unsigned int i = 0; i < invent.size(); i++) {

		int x = invent[i].mX;
		int y = invent[i].mY;
		//mochila[i]->setInventario(this);
		matriz[x][y].ID = invent[i].ID;
		matriz[x][y].objects++;
		matriz[x][y].empty = false;

		GameComponent* gc = new GameComponent(game);
		Vector2D position0(x, y);
		double width = 70;
		double height = 70;

		gc->setText(food); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
		gc->addRenderComponent(rcF); gc->addInputComponent(MSC);  gc->addInputComponent(MSOC);

		stage.push_back(gc);

		//mochila[i]->setComprado();
		//stage.push_back(invent[i]);

		ocupados++;
	}


	//Creamos la imagen que va por encima de la mochila para que no se vea al hacer scroll
	GameComponent* frontShop = new GameComponent(game);
	frontShop->setText(front); frontShop->addRenderComponent(rc);
	stage.push_back(frontShop);

	//Creamos botón para volver al menú principal
	Button* bottonBack = new Button(gamePtr, toMenu, 0);

	Vector2D position0(7, 6);

	double width = 150;
	double height = 100;

	bottonBack->setText(bot); bottonBack->setPosition(position0); bottonBack->setWidth(width); bottonBack->setHeight(height);
	bottonBack->addRenderComponent(rcF); bottonBack->addInputComponent(MIC);

	stage.push_back(bottonBack);

	/*
	//////////////////////////////////CREAMOS LOS ITEMS DE LA TIENDA\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	for (int i = 0; i < 4; i++)
		stage.push_back(new Item(this, game, Prueba, 637 + i * 120, 110, 100, 100, 50, false, -1, -1, 1));

	for (int i = 0; i < 4; i++)
		stage.push_back(new Item(this, game, Prueba3, 637 + i * 120, 210, 100, 100, 150, false, -1, -1, 2));




}

/*


bool ShopState::devMat(int& x, int& y, int ident, Item* elemento) {
	bool aceptada = false;
	/*int auxX;
	int auxY;
	int auxW;
	int auxH;
	int auxMx;
	int auxMy;
	bool encontrado = false;
	bool aceptada = false;
	list<GameObject*>::iterator it = stage.begin();
	while (it != stage.end() && !encontrado) {

		Item* aux = dynamic_cast<Item*>((*it));
		if (aux != nullptr)
			if (static_cast<Item*>((*it))->getSP()) {

				auxX = static_cast<Item*>(*it)->getX();
				auxY = static_cast<Item*>(*it)->getY();
				auxW = static_cast<Item*>(*it)->getW();
				auxH = static_cast<Item*>(*it)->getH();
				auxMx = static_cast<Item*>(*it)->getmX();
				auxMy = static_cast<Item*>(*it)->getmY();

				if (x > (auxX) && x < ((auxX)+auxW) && y >(auxY) && y < ((auxY)+auxH)) {
					encontrado = true;
					x = auxX + auxW / 2;
					y = auxY + auxH / 2;
					//cout << x << "," << y << "," << auxX << "," << auxY << "," << auxW << "," << auxH << endl;
				}
			}
		++it;
	}

	if (encontrado) {

		if (matriz[auxMx][auxMy].empty == true || matriz[auxMx][auxMy].identificador == ident) {

			if (matriz[auxMx][auxMy].empty == true) {
				matriz[auxMx][auxMy].identificador = ident;
				matriz[auxMx][auxMy].empty = false;
				matriz[auxMx][auxMy].x = x;
				matriz[auxMx][auxMy].y = y;
				ocupados++;
			}

			else {

				matriz[auxMx][auxMy].cantidad++;
				cout << "Tienes " << matriz[auxMx][auxMy].cantidad << " elementos del tipo " << ident << " en tu inventario ahora." << endl;
			}
			mochila.push_back(elemento);
			//cout << mochila.size() << endl;
			aceptada = true;

			if (numSP - ocupados == 1)
				creaFila();
		}
	}*/
	//return aceptada;
}

void ShopState::creaFila() {

	actFilas++;

	for (int i = 0; i < 3; i++)
	{
		numSP++;
		matriz[i][actFilas].empty = true;
		matriz[i][actFilas].ID = 0;
		matriz[i][actFilas].objects = 0;

		GameComponent* gc = new GameComponent(game);
		Vector2D position0(2 * i + 2, ultimaFilaY + 2);
		double width = 70;
		double height = 70;

		gc->setText(standPoint); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
		gc->addRenderComponent(rcF); gc->addInputComponent(MSC);  gc->addInputComponent(MSOC);

		stage.push_back(gc);
	}
	ultimaFilaY += 2;
	
}

void ShopState::cambiaDinero(int n) {

	money = money - n;
}

void ShopState::toMenu(Game* game) {
	
	StateMachine* sm = game->getStateMachine();
	sm->popState();
}

ShopState::~ShopState()
{

}