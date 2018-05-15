#include "BagXboxControllerComponent.h"



BagXboxControllerComponent::BagXboxControllerComponent(int iniX, int iniY, int col, int fil, int dis, vector<GameObject*> v, BackPack* b, ShopState* s)
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

	if (XboxController::Instance()->getNumControllers() == 0) //SOLO UN MANDO
		XboxController::Instance()->insertController();

}


BagXboxControllerComponent::~BagXboxControllerComponent()
{

}


bool BagXboxControllerComponent::handleEvent(GameObject* o, const SDL_Event& event) {
	bool handledEvent = false;

	if (event.type == SDL_JOYHATMOTION) {
		Vector2D position = o->getPosition();
		double posY = position.getY();
		double posX = position.getX();

		if (event.jhat.value & SDL_HAT_UP) {

			posY -= distance;
			if (posY >= Y_) {
				position.setY(posY - 0.7);
				j--;
				knowWhereWeAre_ -= 1;
			}
			o->setPosition(position);
		}
		else if (event.jhat.value & SDL_HAT_DOWN) {

			posY += distance;
			if (posY <= col_ * Y_ + 1) {
				position.setY(posY + 0.7);
				knowWhereWeAre_ += 1;
				j++;
			}
			o->setPosition(position);
		}
		else if (event.jhat.value & SDL_HAT_RIGHT) {

			posX += distance;
			if (posX <= fil_ + X_ + 1) {
				position.setX(posX + 0.7);
				knowWhereWeAre_ += 6;
				i++;
			}

			o->setPosition(position);
		}
		else if (event.jhat.value & SDL_HAT_LEFT) {


			posX -= distance;
			if (posX >= X_) {
				position.setX(posX - 0.7);
				knowWhereWeAre_ -= 6;
				i--;
			}
			o->setPosition(position);
		}
	}
	
	else if (event.type == SDL_JOYBUTTONDOWN) {
		Vector2D position = o->getPosition();
		double posY = position.getY();
		double posX = position.getX();

		XboxController::Instance()->onJoystickButtonDown(event);

		if (XboxController::Instance()->getButtonState(0, 0)) { //Si se ha pulsado la A
			vector<estado> sp = bag->getSP();
			//copio el inventario
			Inventary.clear();
			vector<estado>inv = bag->getInvent();
			vector<estado> aux;
			for (int c = 0; c < inv.size(); c++) {
				if (!inv[c].equiped)
					Inventary.push_back(inv[c]);
				else aux.push_back(inv[c]);
			}

			std::cout << "INVETNARIO : " << inv.size() << endl;
			std::cout << "EQUIPED : " << aux.size() << endl;

			if (Inventary.size() != 0 && !sp[knowWhereWeAre_].empty) {
				
			
				Inventary[knowWhereWeAre_].equiped = true;

			
					//Si tenemos hueco en los SP del personaje
					if (bag->getEItems() < 2) {

						//Si la casilla izquierda de la mochila est� libre
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
						//Buscamos el SP que hemos dejado atr�s, donde estaba el objeto, y le decimos que est� vac�o
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
						StringToScreen::Instance()->setMessage("�Desequipa algo! ");
						StringToScreen::Instance()->startMessagin();
					}
					for (int p = 0; p < aux.size(); p++) {
						Inventary.push_back(aux[p]);
					}

				GameManager::Instance()->changeInventory(Inventary);
				bag->setInvent(Inventary);
				bag->setSP(sp);

			}
		}

		else if (XboxController::Instance()->getButtonState(0, 2)) {
			//Si est� !equiped, lo ponemos en un lugar vac�o en los SP

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

		else if (XboxController::Instance()->getButtonState(0, 1)) {
			StateMachine* sm = Game::Instance()->getStateMachine();
			sm->popState();
		}

		else if (event.type == SDL_JOYBUTTONUP)
			XboxController::Instance()->onJoystickButtonUp(event);
	}
	return handledEvent;
}
