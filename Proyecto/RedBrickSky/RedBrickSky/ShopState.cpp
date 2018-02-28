#include "ShopState.h"
#include "Button.h"

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
	food = gamePtr->getTexture(4); //Item1
	food2 = gamePtr->getTexture(5);

	//Componentes necesarios
	rcF = new RenderFrameComponent(); //Render Frame
	rc = new RenderFullComponent(); //Render FS
	MSC = new MouseScrollShopComponent(this);
	MSOC = new MouseOverObjectComponent();
	MIC = new MouseInputComponentButton();
	Info = new MouseInfoClickComponent();

	//Imagen de fondo de la tienda
	GameComponent* backShop = new GameComponent(game);
	backShop->setText(back); backShop->addRenderComponent(rc);
	stage.push_back(backShop);

	shopObjects.resize(2);
	shopObjects[0] = invent[0];

	shopObjects[1].empty = false;
	shopObjects[1].comprado = true;
	shopObjects[1].ID = 2;
	shopObjects[1].objects = 1;
	shopObjects[1].x = 2;
	shopObjects[1].y = 2;
	shopObjects[1].mX = 1;
	shopObjects[1].mY = 0;
	shopObjects[1].price = 100;
	shopObjects[1].tx = food2;
	shopObjects[1].type = 1; //Es una poción

	//Creamos la matriz
	matriz = new estado*[3];
	for (int i = 0; i < 3; i++) {
		matriz[i] = new estado[2];
	}
	//La rellenamos DE SP
	//tenemos en cuenta que estos son los StanPoints que se encuentran en la mochila dentro de la tienda. Los que están
	//en la tienda como tal son diferentes, ya que los elementos de la tienda son fijos
	int aux = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++) {
			double width = 70;
			double height = 70;
			matriz[i][j].empty = true;
			matriz[i][j].ID = 0;
			matriz[i][j].objects = 0;
			matriz[i][j].w = width;
			matriz[i][j].h = height;
			matriz[i][j].mX = i;
			matriz[i][j].mY = j;
			matriz[i][j].objectID = aux;
			matriz[i][j].type = -1;

		//cout << matriz[i][j].mX << "," << matriz[i][j].mY << "," << endl;

			Vector2D position0(2 * i + 2, 2 * j + 2);
			matriz[i][j].x = position0.getX();
			matriz[i][j].y = position0.getY();
			GameComponent* gc = new GameComponent(game);
			InputComponent* auxSCP = new MouseScrollShopComponent(this, aux);
			
			gc->setText(standPoint); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
			gc->addRenderComponent(rcF); gc->addInputComponent(auxSCP);  gc->addInputComponent(MSOC); 

			stage.push_back(gc);
			SP.push_back(matriz[i][j]);
			numSP++;
			aux++;
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
		matriz[x][y].comprado = true;
		matriz[x][y].price = invent[i].price;
		matriz[x][y].tx = invent[i].tx;
		matriz[x][y].type = invent[i].type;

		if (invent[i].tx != nullptr)
			matriz[x][y].tx = invent[i].tx;
		else
			matriz[x][y].tx = food;

		GameComponent* gc = new GameComponent(game);
		Vector2D position0(matriz[x][y].x, matriz[x][y].y);
		double width = 70;
		double height = 70;

		gc->setText(matriz[x][y].tx); gc->setPosition(position0); gc->setWidth(width); gc->setHeight(height);
		gc->addRenderComponent(rcF); gc->addInputComponent(MSC);  gc->addInputComponent(Info);

		stage.push_back(gc);
		GCInventV.push_back(gc);

		ocupados++;
	}

	//Creación de los items que tendrá la tienda

	for (int i = 0; i < shopObjects.size(); i++) {

		Texture* txt;

		if (shopObjects[i].tx == nullptr)
			txt = food;
		else
			txt = shopObjects[i].tx;
		
		GameComponent* gc = new GameComponent(game);
		Vector2D position5(i + 10, 2);
		Vector2D oriPos(i + 10, 2);
		DragNDropShopComponent* p = new DragNDropShopComponent(this, shopObjects[i].price, false, shopObjects[i].ID, gc, shopObjects[i].type);
		gc->setText(txt); gc->setOriPos(oriPos); gc->setPosition(position5); gc->setWidth(70); gc->setHeight(70);
		gc->addRenderComponent(rcF); gc->addInputComponent(p); gc->addInputComponent(Info);	gc->addInputComponent(MSC);

	
		GameComponent* gc2 = new GameComponent(game);
		gc2->setText(txt); gc2->setOriPos(oriPos); gc2->setPosition(position5); gc2->setWidth(70); gc2->setHeight(70);
		gc2->addRenderComponent(rcF); gc2->addInputComponent(MSC);

		stageBack(gc2);
		stageBack(gc);
		GCshopV.push_back(gc);
		
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
		SP.push_back(matriz[i][actFilas]);

	}
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