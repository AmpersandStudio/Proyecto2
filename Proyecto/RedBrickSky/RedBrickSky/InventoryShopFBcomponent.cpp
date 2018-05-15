#include "InventoryShopFBcomponent.h"



KeyBoardBackPackComponent::KeyBoardBackPackComponent(int iniX, int iniY, int col, int fil, int dis, vector<GameObject*> v, BackPack* b, ShopState* s)
{
	X_ = iniX;
	Y_ = iniY;
	col_ = col;
	fil_ = fil;
	distance = dis;
	SP = v;
	bag = b;
	shop = s;
	knowWhereWeAre_ = 0;
}


KeyBoardBackPackComponent::~KeyBoardBackPackComponent()
{
}

bool KeyBoardBackPackComponent::handleEvent(GameObject* o, const SDL_Event& event) {
	bool handledEvent = false;


	if (event.type == SDL_KEYDOWN) {
		Vector2D position = o->getPosition();
		double posY = position.getY();
		double posX = position.getX();

		if (event.key.keysym.sym == SDLK_UP) {

			posY -= distance;
			if (posY >= Y_) {
				position.setY(posY - 0.7);
				knowWhereWeAre_ -= 1;
				j--;
			}
			o->setPosition(position);
		}
		else if (event.key.keysym.sym == SDLK_DOWN) {

			posY += distance;
			if (posY <= col_ * Y_ + 1) {
				position.setY(posY + 0.7);
				knowWhereWeAre_ += 1;
				j++;
			}
			o->setPosition(position);
		}
		else if (event.key.keysym.sym == SDLK_RIGHT) {

			posX += distance;
			if (posX <= fil_ + X_ + 1) {
				position.setX(posX + 0.7);
				knowWhereWeAre_ += 6;
				i++;
			}

			o->setPosition(position);
		}
		else if (event.key.keysym.sym == SDLK_LEFT) {

			posX -= distance;
			if (posX >= X_) {
				position.setX(posX - 0.7);
				knowWhereWeAre_ -= 6;
				i--;
			}
			o->setPosition(position);
		}


		else if (event.key.keysym.sym == SDLK_SPACE) {
			vector<estado> sp = bag->getSP();
			//copio el inventario
			Inventary.clear();
			Inventary = bag->getInvent();
			if (Inventary.size() != 0 && !sp[knowWhereWeAre_].empty) {
				//marco el elemento como comprado != comprado

				Inventary[knowWhereWeAre_].equiped = true;


				//Si tenemos hueco en los SP del personaje
				if (bag->getEItems() < 2) {

					//Si la casilla izquierda de la mochila está libre
					if (!bag->getLeft()) {
						Vector2D position0(2.6, 9.7);
						Inventary[knowWhereWeAre_].GC->setPosition(position0);
						bag->setLeft(true);
						isLeft = true;
					}
					else {
						Vector2D position1(5.8, 9.7);
						Inventary[knowWhereWeAre_].GC->setPosition(position1);
					}
					//Actualizamos la mochila
					bag->pushEItem();
					bag->pushEquipedItem(Inventary[knowWhereWeAre_]);
					//Buscamos el SP que hemos dejado atrás, donde estaba el objeto, y le decimos que está vacío
					for (int i = 0; i < sp.size(); i++)
					{
						if (sp[i].ID == knowWhereWeAre_) {
							sp[i].empty = true;

						}
					}
				}

				else {
					Inventary[knowWhereWeAre_].equiped = false;
					//Lanzamos un mensaje diciendo que hay que quitar un objeto
					StringToScreen::Instance()->renderBackGround();
					StringToScreen::Instance()->setMessage("¡Desequipa algo! ");
					StringToScreen::Instance()->startMessagin();
				}



				GameManager::Instance()->changeInventory(Inventary);
				bag->setInvent(Inventary);
				bag->setSP(sp);

			}
		}
		else if (event.key.keysym.sym == SDLK_BACKSPACE) {
			//Si está !equiped, lo ponemos en un lugar vacío en los SP
			std::cout << "Hol caracoasl" << endl;
			Inventary.clear();
			Inventary = bag->getInvent();

			for each (estado S in bag->getEquipedItems())
			{

				vector<estado> sp = bag->getSP();
				bag->pullEitem();
				bag->setLeft(false);

				isLeft = false;
				//Buscamos la primera casilla libre

				int aux = 0;
				int i = 0;
				int j = 0;
				bool place = false;
				while (i < 3 && !place) {
					if (j > 6) {
						i++;
						j = 0;
					}

					if (sp[aux].empty == true) {
						Vector2D p(sp[aux].x, sp[aux].y);
						S.GC->setPosition(p);//createItemAtSP(x, y, auxV[p].objectID, auxV[p]);
						sp[aux].empty = false;
						place = true;
						S.equiped = false;
						bool found = false;
						int h = 0;
						while (h < Inventary.size() && !found)
						{
							if (Inventary[h].ID == S.ID) {
								Inventary[h].equiped = false;
								found = true;
							}
							else h++;
						}
					}
					else {
						j++;
						aux++;
					}
				}
				GameManager::Instance()->changeInventory(Inventary);
				bag->setInvent(Inventary);
				bag->setSP(sp);
			}
			bag->pullEquipedItem();
		}
	}

	else if (event.type == SDL_MOUSEMOTION){
	
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y); //comprobamos estado del raton

		int i = 0;

		int auxX;
		int auxY;
		int auxW;
		int auxH;
		int auxMx;
		int auxMy;

		for(unsigned int i = 0; i < SP.size(); i++) {
			//Busca si el objeto se ha dejado en alguno de los Stand Points
			{
				auxW = SP[i]->getWidth();
				auxH = SP[i]->getHeight();
				auxX = SP[i]->getPosition().getX() * auxW;
				auxY = SP[i]->getPosition().getY() * auxH;

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