#include "ShopState.h"
#include "Button.h"
#include "GameComponent.h"
#include "RenderFullComponent.h"

ShopState::ShopState(Game* gamePtr) : GameState (gamePtr)
{
	game = gamePtr; 

	GameComponent* gc = new GameComponent(game);
	Texture* tx0 = gamePtr->getTexture(6);

	RenderComponent* rc = new RenderFullComponent();


	gc->setText(tx0); gc->addRenderComponent(rc);


	stage.push_back(gc);

	for (int i = 0; i < 4; i++) {
		GameComponent* gc = new GameComponent(game);
		Texture* tx0 = gamePtr->getTexture(8);
		Vector2D position0(1.7 * i + 1.5, 2);
		double width = 70;
		double height = 70;

		RenderComponent* rc = new RenderFrameComponent();

		gc->setText(tx0); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height); gc->addRenderComponent(rc);


		stage.push_back(gc);
	}

	

	//Puntero al juego


					//ESTO IRIA DENTRO DEL GAME MANAGER
					/*private:

					vector<Item> mochila;
					int dinero = 340;

					public:
					GameManager();
					~GameManager();
					Item getN(int n) { return mochila[n]; };
					int tamMochila() { return mochila.size(); };
					void meteEnMochila(Item t) { mochila.push_back(t); };
					int getDinero() { return dinero; };*/


	/*txF = g->getTexture(20);
	txF2 = g->getTexture(21);
	Prueba = g->getTexture(3);
	Prueba2 = g->getTexture(12);
	Prueba3 = g->getTexture(4);

	stage.push_back(new Button(toMenu, game, g->getTexture(17), 1000, 500, 200, 100));

	dinero = 340;
	ocupados = 0;
	elementos = 0;
	actFilas = 0;
	cout << "Tu dinero actual es: " << dinero << endl;

	int xM = 0; int yM = 0;

	//Creamos la matriz
	matriz = new estado*[4];
	for (int i = 0; i < 4; i++) {
		matriz[i] = new estado[1];
	}

	//La rellenamos
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 2; j++) {
			matriz[i][j].empty = true;
			matriz[i][j].identificador = 0;
			matriz[i][j].cantidad = 0;
			stage.push_back(new Item(this, game, Prueba2, 90 + 120 * i, 105 * (j + 2), 100, 100, 50, true, i, j, 0));
			elementos++;
		}
	ultimaFilaY = 315;
	actFilas = 1;

	//////////////////////////////////CREAMOS LOS ITEMS DE LA TIENDA\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	for (int i = 0; i < 4; i++)
		stage.push_back(new Item(this, game, Prueba, 637 + i * 120, 110, 100, 100, 50, false, -1, -1, 1));

	for (int i = 0; i < 4; i++)
		stage.push_back(new Item(this, game, Prueba3, 637 + i * 120, 210, 100, 100, 150, false, -1, -1, 2));

	//CREAMOS UN ITEM PARA TENER DENTRO DE LA MOCHILA, ESTO DESPUES SE ELIMINARÁ 
	Item* nuevo = new Item(this, game, Prueba3, 637, 210, 100, 100, 150, false, 0, 0, 2);
	nuevo->setComprado();
	mochila.push_back(nuevo);

	//matriz[mochila[0]->getmX()][mochila[0]->getmY()].x = 90;
	//matriz[mochila[0]->getmX()][mochila[0]->getmY()].y = 210;

	//Asginamos los elementos dentro del vector de la mochila a cada casilla
	for (int i = 0; i < mochila.size(); i++) {

		int x = mochila[i]->getmX();
		int y = mochila[i]->getmY();
		mochila[i]->setInventario(this);
		matriz[x][y].identificador = mochila[i]->getIdentificador();
		matriz[x][y].cantidad++;
		matriz[x][y].empty = false;
		mochila[i]->setX(matriz[x][y].x);
		mochila[i]->setY(matriz[x][y].y);
		mochila[i]->setComprado();
		stage.push_back(mochila[i]);

		ocupados++;
	}*/

}

ShopState::~ShopState()
{
}

//bool ShopState::handleEvent(SDL_Event& event) {

	//bool handledEvent = false;
	/*handledEvent = (GameState::handleEvent(event));

	if (event.wheel.y == 1) // scroll up
	{
		for (list<GameObject*>::iterator it = stage.begin();
			it != stage.end(); ++it) {
			Item* aux = dynamic_cast<Item*>((*it));
			if (aux != nullptr)
				if (static_cast<Item*>((*it))->getSP()) {
					int auxY = dynamic_cast<Item*>(*it)->getY();
					static_cast<Item*>(*it)->setY(auxY - 20);
					ultimaFilaY -= 20;

				}
		}

		for (list<GameObject*>::iterator it = stage.begin();
			it != stage.end(); ++it) {
			Item* aux = dynamic_cast<Item*>((*it));
			if (aux != nullptr)
				if (!static_cast<Item*>((*it))->getSP() && static_cast<Item*>((*it))->getComprado())
				{
					int auxY = static_cast<Item*>(*it)->getY();
					static_cast<Item*>(*it)->setY(auxY - 20);
				}
		}
	}
	else if (event.wheel.y == -1) // scroll down
	{

		for (list<GameObject*>::iterator it = stage.begin();
			it != stage.end(); ++it) {
			Item* aux = dynamic_cast<Item*>((*it));
			if (aux != nullptr)
				if (static_cast<Item*>((*it))->getSP()) {
					int auxY = static_cast<Item*>(*it)->getY();
					static_cast<Item*>(*it)->setY(auxY + 20);
					ultimaFilaY += 20;
				}
		}

		for (list<GameObject*>::iterator it = stage.begin();
			it != stage.end(); ++it) {
			Item* aux = dynamic_cast<Item*>((*it));
			if (aux != nullptr)
				if (!static_cast<Item*>((*it))->getSP() && static_cast<Item*>((*it))->getComprado()) {
					int auxY = static_cast<Item*>(*it)->getY();
					static_cast<Item*>(*it)->setY(auxY + 20);
				}
		}
	}*/
	//return handledEvent;
//}

//void ShopState::render() {

	/*txF->renderComplete();

	for (list<GameObject*>::iterator it = stage.begin();
		it != stage.end(); ++it) {
		Item* aux = dynamic_cast<Item*>((*it));
		if (aux != nullptr)
			if (static_cast<Item*>((*it))->getSP())
				(*it)->render();
	}

	for (list<GameObject*>::iterator it = stage.begin();
		it != stage.end(); ++it) {
		Item* aux = dynamic_cast<Item*>((*it));
		if (aux != nullptr)
			if (!static_cast<Item*>((*it))->getSP() && static_cast<Item*>((*it))->getComprado()) {
				(*it)->render();

			}
	}

	txF2->renderComplete();

	for (list<GameObject*>::iterator it = stage.begin();
		it != stage.end(); ++it) {
		Item* aux = dynamic_cast<Item*>((*it));
		if (aux != nullptr)
			if (!static_cast<Item*>((*it))->getSP() && !static_cast<Item*>((*it))->getComprado())
				(*it)->render();
	}

	for (list<GameObject*>::iterator it = stage.begin();
		it != stage.end(); ++it) {
		Button* aux = dynamic_cast<Button*>((*it));
		if (aux != nullptr) {
			(*it)->render();
		}
	}
	*/
//}

void ShopState::cambiaDinero(int n) {

	dinero = dinero - n;
}

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

			if (elementos - ocupados == 1)
				creaFila();
		}
	}*/
	return aceptada;
}

void ShopState::mouseEncima(int x, int y) {
	
	/*int auxX;
	int auxY;
	int auxW;
	int auxH;

	bool encontrado = false;
	bool aceptada = false;
	list<GameObject*>::iterator it;
	for (it = stage.begin(); it != stage.end(); ++it) {

		Item* aux = dynamic_cast<Item*>((*it));
		if (aux != nullptr)
			if (static_cast<Item*>((*it))->getSP()) {

				auxX = static_cast<Item*>(*it)->getX();
				auxY = static_cast<Item*>(*it)->getY();
				auxW = static_cast<Item*>(*it)->getW();
				auxH = static_cast<Item*>(*it)->getH();

				if (x > (auxX) && x < ((auxX)+auxW) && y >(auxY) && y < ((auxY)+auxH)) {
					static_cast<Item*>((*it))->cambiaSprite(1);
				}
				else
					static_cast<Item*>((*it))->cambiaSprite(0);
			}
	}*/
	
}

void ShopState::vuelveNormal() {

	/*list<GameObject*>::iterator it;
	for (it = stage.begin(); it != stage.end(); ++it) {

		Item* aux = dynamic_cast<Item*>((*it));
		if (aux != nullptr)
			if (static_cast<Item*>((*it))->getSP()) {
				static_cast<Item*>((*it))->cambiaSprite(0);
			}
	}
	*/
}

void ShopState::creaFila() {

/*	actFilas++;

	for (int i = 0; i < 4; i++)
	{
		elementos++;
		matriz[i][actFilas].empty = true;
		matriz[i][actFilas].identificador = 0;
		matriz[i][actFilas].cantidad = 0;
		stage.push_back(new Item(this, game, Prueba2, 90 + 120 * i, ultimaFilaY + 105, 100, 100, 50, true, i, actFilas, 0));
	}
	ultimaFilaY = ultimaFilaY + 105;
	*/
}

void ShopState::toMenu(Game* game) {
	/*
	StateMachine* sm = game->getStateMachine();
	sm->popState();*/


}