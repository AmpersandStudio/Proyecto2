#include "InventoryShopFBcomponent.h"



KeyBoardBackPackComponent::KeyBoardBackPackComponent(int iniX, int iniY, int col, int fil, int dis, vector<GameObject*> v, BackPack* b, ShopState* s)
{
	X_ = iniX;
	Y_ = iniY;
	col_ = col;
	fil_ = fil;
	distance = dis;
	SP = v;
	back = b;
	shop = s;
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
				position.setY(posY);
				j--;
			}
			o->setPosition(position);
		}
		else if (event.key.keysym.sym == SDLK_DOWN) {
			
			posY += distance;
			if (posY <= col_ * Y_) {
				position.setY(posY);
				j++;
			}
			o->setPosition(position);
		}
		else if (event.key.keysym.sym == SDLK_RIGHT) {
			
			posX += distance;
			if (posX <= fil_ + X_ + 2) {
				position.setX(posX);
				i++;
			}

			o->setPosition(position);
		}
		else if (event.key.keysym.sym == SDLK_LEFT) {
			
			posX -= distance;
			if (posX >= X_) {
				position.setX(posX);
				i--;
			}
			o->setPosition(position);
		}

		else if (event.key.keysym.sym == SDLK_SPACE) {
			invent.clear();
			if(back != nullptr)
				invent = back->getInvent();

			if (selection_) {
				
				invent[savedInvent].x = posX - 9;
				invent[savedInvent].y = posY;
				invent[savedInvent].mX = i;
				invent[savedInvent].mY = j;

				
				Vector2D pos(posX, posY);
				invent[savedInvent].GC->setPosition(pos);
				invent[savedInvent].GC->setOriPos(pos);
				selection_ = false;

				if(back != nullptr)
					back->setInvent(invent);
			}

			else {
				int  i = 0;
				bool encontrado = false;
				while (i < invent.size() && !encontrado) {

					if (invent[i].x == (posX - 9) && invent[i].y == (posY))
						encontrado = true;
					else
						i++;
				}

				if (encontrado) {
					savedInvent = i;
					selection_ = true;
				}
			}


		}

		//El siguiente bucle Cambia el color del SP en el que estamos y pone los dem�s normales
		for (int p = 0; p < SP.size(); p++)
		{
			if (SP[p]->getPosition().getX() == o->getPosition().getX() &&
				SP[p]->getPosition().getY() == o->getPosition().getY()) {

				SP[p]->setColFrame(1);
			}
			else
				SP[p]->setColFrame(0);
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

		for(int i = 0; i < SP.size(); i++) {
			//Busca si el objeto se ha dejado en alguno de los Stand Points
			{
				auxX = SP[i]->getPosition().getX() * 70;
				auxY = SP[i]->getPosition().getY() * 70;
				auxW = SP[i]->getWidth();
				auxH = SP[i]->getHeight();;

				//cout  << auxY << "," << endl;

				if (x >(auxX) && x < ((auxX)+auxW) && y >(auxY) && y < ((auxY)+auxH)) {
					SP[i]->setColFrame(1);
					Vector2D pos;
					pos.setX(auxX / 70);
					pos.setY(auxY / 70);
					o->setPosition(pos);
				}

				else
					SP[i]->setColFrame(0);
			}
		}
	}
	return handledEvent;
}