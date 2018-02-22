#include "ShopState.h"
#include "Button.h"
#include "GameComponent.h"


ShopState::ShopState(Game* gamePtr) : GameState (gamePtr)
{
	game = gamePtr; 

	//Texturas necesitadas
	back = gamePtr->getTexture(6);
	standPoint = gamePtr->getTexture(8);
	front = gamePtr->getTexture(7);
	bot = gamePtr->getTexture(3); //Para el botón

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
	matriz = new estado*[4];
	for (int i = 0; i < 4; i++) {
		matriz[i] = new estado[1];
	}

	//La rellenamos /////////////////////(ESTE CODIGO DESENCADENA UN ERROR DE MEMORIA)\\\\\\\\\\\\\\\\\

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 2; j++) {
			matriz[i][j].empty = true;
			matriz[i][j].identificador = 0;
			matriz[i][j].cantidad = 0;
			GameComponent* gc = new GameComponent(game);
			Vector2D position0(1.7 * i + 1.5, 2 * j + 2);
			double width = 70;
			double height = 70;

			gc->setText(standPoint); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
			gc->addRenderComponent(rcF); gc->addInputComponent(MSC);  gc->addInputComponent(MSOC);

			stage.push_back(gc);
			elementos++;
		}
	ultimaFilaY = 4;
	actFilas = 1;

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

	creaFila();
	creaFila();

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

	dinero = 340;
	ocupados = 0;
	elementos = 0;
	actFilas = 0;
	cout << "Tu dinero actual es: " << dinero << endl;

	int xM = 0; int yM = 0;


	//////////////////////////////////CREAMOS LOS ITEMS DE LA TIENDA\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	for (int i = 0; i < 4; i++)
		stage.push_back(new Item(this, game, Prueba, 637 + i * 120, 110, 100, 100, 50, false, -1, -1, 1));

	for (int i = 0; i < 4; i++)
		stage.push_back(new Item(this, game, Prueba3, 637 + i * 120, 210, 100, 100, 150, false, -1, -1, 2));


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

void ShopState::creaFila() {

	actFilas++;

	for (int i = 0; i < 4; i++)
	{
		elementos++;
		matriz[i][actFilas].empty = true;
		matriz[i][actFilas].identificador = 0;
		matriz[i][actFilas].cantidad = 0;

		GameComponent* gc = new GameComponent(game);
		Vector2D position0(1.7 * i + 1.5, ultimaFilaY + 2);
		double width = 70;
		double height = 70;

		gc->setText(standPoint); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
		gc->addRenderComponent(rcF); gc->addInputComponent(MSC);  gc->addInputComponent(MSOC);

		stage.push_back(gc);
	}
	ultimaFilaY += 2;
	
}

void ShopState::toMenu(Game* game) {
	
	StateMachine* sm = game->getStateMachine();
	sm->popState();


}

