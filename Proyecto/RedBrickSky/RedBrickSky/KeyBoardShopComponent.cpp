#include "KeyBoardShopComponent.h"
#include "ShopState.h"


KeyBoardShopComponent::KeyBoardShopComponent(int iniX, int iniY, int col, int fil, int dis, vector<GameObject*> v, BackPack* b, ShopState* s)
{
	X_ = iniX;
	Y_ = iniY;
	col_ = col;
	fil_ = fil;
	distance = dis;
	SP = v;
	shop = s;

	knowWhereWeAre_ = 0;
}

KeyBoardShopComponent::~KeyBoardShopComponent()
{
}

bool KeyBoardShopComponent::handleEvent(GameObject* o, const SDL_Event& event) {
	bool handledEvent = false;


	if (event.type == SDL_KEYDOWN) {

		vector<estado> elementosTienda = GameManager::Instance()->copyShopItems();
		vector<estado> sp = shop->getSP();
		
		Vector2D position = o->getPosition();
		double posY = position.getY();
		double posX = position.getX();

		if (event.key.keysym.sym == SDLK_UP) {

			if (posY > Y_ + 1) {
				posY -= distance* 0.75;
				knowWhereWeAre_ -= 8;
				StringToScreen::Instance()->setMessage("Nombre: " + elementosTienda[knowWhereWeAre_].nombre + " ");
				StringToScreen::Instance()->setMessage("Precio: " + std::to_string(elementosTienda[knowWhereWeAre_].price) + " ");
				StringToScreen::Instance()->startMessagin();
			}

			if (posX >= Y_) {
				position.setY(posY);
				j--;
			}
			o->setPosition(position);
		}
		else if (event.key.keysym.sym == SDLK_DOWN) {

			if (posY < Y_ + fil_ - 2) {
				posY += distance * 0.75;
				knowWhereWeAre_ += 8;
				StringToScreen::Instance()->setMessage("Nombre: " + elementosTienda[knowWhereWeAre_].nombre + " ");
				StringToScreen::Instance()->setMessage("Precio: " + std::to_string(elementosTienda[knowWhereWeAre_].price) + " ");
				StringToScreen::Instance()->startMessagin();
			}
			if (posY <= Y_ + fil_) {
				position.setY(posY);
				j++;
			}
			o->setPosition(position);
		}
		else if (event.key.keysym.sym == SDLK_RIGHT) {

			if (posX < X_ + col_ - 1) {
				posX += distance / 2;
				knowWhereWeAre_++;
				StringToScreen::Instance()->setMessage("Nombre: " + elementosTienda[knowWhereWeAre_].nombre + " ");
				StringToScreen::Instance()->setMessage("Precio: " + std::to_string(elementosTienda[knowWhereWeAre_].price) + " ");
				StringToScreen::Instance()->startMessagin();
			}
			if (posX <= X_ + col_ - 1) {
				position.setX(posX);
				i++;
			}

			o->setPosition(position);
		}
		else if (event.key.keysym.sym == SDLK_LEFT) {


			if (posX >= X_) {
				posX -= distance / 2;

			}

			if (posX >= X_) {
				knowWhereWeAre_--;
				position.setX(posX);
				StringToScreen::Instance()->setMessage("Nombre: " + elementosTienda[knowWhereWeAre_].nombre + " ");
				StringToScreen::Instance()->setMessage("Precio: " + std::to_string(elementosTienda[knowWhereWeAre_].price) + " ");
				StringToScreen::Instance()->startMessagin();
				i--;
			}

			o->setPosition(position);
		}

		else if (event.key.keysym.sym == SDLK_SPACE) {
			//std::cout << "Donde estamos: " << elementosTienda[knowWhereWeAre_].nombre << endl;
			if (GameManager::Instance()->getMoney() >= elementosTienda[knowWhereWeAre_].price && !elementosTienda[knowWhereWeAre_].comprado) {

				GameManager::Instance()->setMoney(GameManager::Instance()->getMoney() - elementosTienda[knowWhereWeAre_].price);
				StringToScreen::Instance()->setMessage("¡Objeto comprado! ");
				StringToScreen::Instance()->startMessagin();
				StringToScreen::Instance()->changeInfinite(0, "Caramelos: " + std::to_string(GameManager::Instance()->getMoney()));

				//Buscamos la primera casilla libre

				int aux = 0;
				Vector2D p;
				int i = 0;
				int j = 0;
				bool place = false;
				while (i < 6 && !place) {
					if (j > 3) {
						i++;
						j = 0;
					}

					if (sp[aux].empty == true) {
						 p.set(sp[aux].x, sp[aux].y);
						sp[aux].empty = false;
						place = true;

					}
					else {
						j++;
						aux++;
					}
				}

				//GameManager::Instance()->changeInventory(Inventary);
				//shop->setInvent(Inventary);
				shop->setSP(sp);


				//if (StandPoints[i].empty == true) {
				//	StandPoints[i].ID = identifier;
				//	StandPoints[i].empty = false;
				//	double posX, posY;
				//	posX = auxX + auxW / 2;
				//	posY = auxY + auxH / 2;

				//	v.set(posX / 45 - 0.5, posY / 45 - 0.5);
				//	o->setPosition(v);

				estado n;
				n.price = elementosTienda[knowWhereWeAre_].price;
				n.comprado = true;
				n.ID = elementosTienda[knowWhereWeAre_].ID;
				n.empty = false;
				//n.objects = StandPoints[i].objects;
				n.x = p.getX();
				n.y = p.getY();
				n.mX = 0;
				n.mY = 0;
				n.w = 45;
				n.h = 45;
				n.tx = elementosTienda[knowWhereWeAre_].tx;
				n.type = 0;
				n.nombre = elementosTienda[knowWhereWeAre_].nombre;
				n.FilFrame = elementosTienda[knowWhereWeAre_].FilFrame;
				n.colFrame = elementosTienda[knowWhereWeAre_].colFrame;

				shop->setInvent(n);
				GameManager::Instance()->setInventory(n);

				Vector2D v(p);
				GameComponent* gc2 = new GameComponent();
				gc2->setTextureId(elementosTienda[knowWhereWeAre_].tx); gc2->setOriPos(v); gc2->setPosition(v); gc2->setWidth(45); gc2->setHeight(45);
				gc2->addRenderComponent(new RenderSingleFrameComponent());
				gc2->setColFrame(n.colFrame); gc2->setRowFrame(n.FilFrame);

				shop->stageBack(gc2);
				elementosTienda[knowWhereWeAre_].comprado = true;
				GameManager::Instance()->changeShopItems(elementosTienda);

			}


			else if (GameManager::Instance()->getMoney() < elementosTienda[knowWhereWeAre_].price) {
				StringToScreen::Instance()->setMessage("¡No tienes dinero para pagar eso!");
				StringToScreen::Instance()->startMessagin();
			}
		}
	}
	

	else if (event.type == SDL_MOUSEMOTION) {

		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y); //comprobamos estado del raton

		int i = 0;

		int auxX;
		int auxY;
		int auxW;
		int auxH;

		for (int i = 0; i < SP.size(); i++) {
			//Busca si el objeto se ha dejado en alguno de los Stand Points
			{
				auxX = SP[i]->getPosition().getX() * 45;
				auxY = SP[i]->getPosition().getY() * 45;
				auxW = SP[i]->getWidth();
				auxH = SP[i]->getHeight();;

				if (x >(auxX) && x < ((auxX)+auxW) && y >(auxY) && y < ((auxY)+auxH)) {
					SP[i]->setColFrame(1);
					}

				else
					SP[i]->setColFrame(0);
			}
		}
	}

	return handledEvent;
}