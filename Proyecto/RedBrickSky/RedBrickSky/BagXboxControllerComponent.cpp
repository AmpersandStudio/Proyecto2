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
			Inventary = bag->getnotEquipedItems();
			std::cout << Inventary.size() << endl;
			if (Inventary.size() != 0 && !sp[knowWhereWeAre_].empty) {

				Inventary[knowWhereWeAre_].equiped = true;
				
				//Si tenemos hueco en los SP del personaje
				if (bag->getEItems() < 2) {

					//Si la casilla izquierda de la mochila está libre
					if (!bag->getLeft()) {
						Vector2D position0(2.6, 9.7);
						Inventary[knowWhereWeAre_].GC->setPosition(position0);
						bag->setLeft(true);
						isLeft = true;

						vector<estado> p;
						for (int i = 0; i < Inventary.size(); i++) {
							if (!Inventary[i].equiped) {
								p.push_back(Inventary[i]);
							}

							else {
								//Actualizamos la mochila
								bag->pushEItem();
								bag->pushEquipedItem(Inventary[knowWhereWeAre_]);
							}
						}

						bag->setNotEquipedItems(p);
						std::cout << "P::::" << p.size() << endl;
					}
					else {
						Vector2D position1(5.8, 9.7);
						Inventary[knowWhereWeAre_].GC->setPosition(position1);

						vector<estado> p;
						for (int i = 0; i < Inventary.size(); i++) {
							if (!Inventary[i].equiped) {
								p.push_back(Inventary[i]);
							}

							else {
								//Actualizamos la mochila
								bag->pushEItem();
								bag->pushEquipedItem(Inventary[knowWhereWeAre_]);
							}
						}
						bag->setNotEquipedItems(p);
						std::cout << "P::::" << p.size() << endl;
					}
				
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

				//GameManager::Instance()->changeInventory(Inventary);
				//bag->setNotEquipedItems(Inventary);
				//bag->setInvent(Inventary);
				bag->setSP(sp);
				move();
				
			}
		}

		else if (XboxController::Instance()->getButtonState(0, 2)) {

			vector<estado> sp = bag->getSP();

			for each (estado S in bag->getEquipedItems())
			{

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
						bag->pushnotEquipedItem(S);
						bool found = false;
						
					}
					else {
						j++;
						aux++;
					}
				}
			}

			bag->pullEquipedItem();

			//GameManager::Instance()->changeInventory(Inventary);
			//bag->setInvent(Inventary);
			bag->setSP(sp);
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

void BagXboxControllerComponent::move() {
	vector<estado> sp = bag->getSP();
	int i = 0;
	bool found = false;
	while (i < sp.size() && !found) {
		if (sp[i].empty)
			found = true;
		else
			i++;
	}

	vector<estado> s = bag->getnotEquipedItems();
	int aux = s.size() - 1;

	Vector2D p(sp[i].x, sp[i].y);
	s[aux].GC->setPosition(p);//createItemAtSP(x, y, auxV[p].objectID, auxV[p]);
	sp[i].empty = false;
	s[aux].equiped = false;

	bag->setSP(sp);
}