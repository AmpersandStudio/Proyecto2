#include "ShopXboxControllerComponent.h"



ShopXboxControllerComponent::ShopXboxControllerComponent(int iniX, int iniY, int col, int fil, int dis, vector<GameObject*> v, BackPack* b, ShopState* s)
{
	X_ = iniX;
	Y_ = iniY;
	col_ = col;
	fil_ = fil;
	distance = dis;
	SP = v;
	shop = s;
	ShopItems* items = new ShopItems();
	shopObjects = items->getItems();
	delete items;

	knowWhereWeAre_ = 0;

	if (XboxController::Instance()->getNumControllers() == 0) //SOLO UN MANDO
		XboxController::Instance()->insertController();
}


ShopXboxControllerComponent::~ShopXboxControllerComponent()
{

}


bool ShopXboxControllerComponent::handleEvent(GameObject* o, const SDL_Event& event) {
	bool handledEvent = false;

	if (event.type == SDL_JOYHATMOTION) {

		vector<estado> elementosTienda = GameManager::Instance()->copyShopItems();

		Vector2D position = o->getPosition();
		double posY = position.getY();
		double posX = position.getX();

		if (event.jhat.value & SDL_HAT_UP) {

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
		else if (event.jhat.value & SDL_HAT_DOWN) {

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
		else if (event.jhat.value & SDL_HAT_RIGHT) {

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
		else if (event.jhat.value & SDL_HAT_LEFT) {

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
	}

	else if (event.type == SDL_JOYBUTTONDOWN) {

		Vector2D position = o->getPosition();
		double posY = position.getY();
		double posX = position.getX();

		XboxController::Instance()->onJoystickButtonDown(event);

		if (XboxController::Instance()->getButtonState(0, 0)) { //Si se ha pulsado la A
			vector<estado> elementosTienda = shop->getShopItems();
			vector<estado> sp = shop->getSP();
			if (GameManager::Instance()->getMoney() >= elementosTienda[knowWhereWeAre_].price) {
				if (!elementosTienda[knowWhereWeAre_].comprado) {

					elementosTienda[knowWhereWeAre_].comprado = true;
					shop->setShopObjects(elementosTienda);
					GameManager::Instance()->changeShopItems(elementosTienda);


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

					shop->setSP(sp);

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

				}
				else if (elementosTienda[knowWhereWeAre_].comprado) {
					StringToScreen::Instance()->setMessage("¡Ya tienes ese arma! ");
					StringToScreen::Instance()->startMessagin();
				}
			}

			else if (GameManager::Instance()->getMoney() < elementosTienda[knowWhereWeAre_].price) {
				StringToScreen::Instance()->setMessage("¡No tienes dinero para pagar eso! ");
				StringToScreen::Instance()->startMessagin();
			}
		}

		else if (XboxController::Instance()->getButtonState(0, 2)) {
			if (GameManager::Instance()->getMoney() >= GameManager::Instance()->getPotionsPrize()) {
				GameManager::Instance()->addPotion();
				GameManager::Instance()->setMoney(GameManager::Instance()->getMoney() - GameManager::Instance()->getPotionsPrize());
				StringToScreen::Instance()->setMessage("¡Pocion comprada! ");
				StringToScreen::Instance()->startMessagin();
				StringToScreen::Instance()->changeInfinite(0, "Caramelos: " + std::to_string(GameManager::Instance()->getMoney()));
				StringToScreen::Instance()->changeInfinite(1, "Comprar pociones      x" + std::to_string(GameManager::Instance()->getPotions()));
			}
			else {
				StringToScreen::Instance()->setMessage("¡No tienes más dinero! ");
				StringToScreen::Instance()->startMessagin();
			}
		}

		else if (XboxController::Instance()->getButtonState(0, 1))
		{
			StateMachine* sm = Game::Instance()->getStateMachine();
			sm->popState();
		}
		XboxController::Instance()->onJoystickButtonUp(event); //Aseguro que levantamos el botón después de usarlo
	}
	if (event.type == SDL_JOYBUTTONUP)
		XboxController::Instance()->onJoystickButtonUp(event);

	return handledEvent;
}