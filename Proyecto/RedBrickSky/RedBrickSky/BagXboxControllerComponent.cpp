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
			Inventary = bag->getInvent();
			
			if (Inventary.size() != 0 && !sp[knowWhereWeAre_].empty && !Inventary[knowWhereWeAre_].equiped) {

				Inventary[knowWhereWeAre_].equiped = true;
				
				//Si tenemos hueco en los SP del personaje
				if (bag->getEItems() < 2) {

					//Si la casilla izquierda de la mochila está libre
					if (!bag->getLeft()) {
						Vector2D position0(2.6, 9.7);
						Inventary[knowWhereWeAre_].equiped = true;
						bag->setLeft(true);
						isLeft = true;
						bag->pushEItem();
						bag->pushEquipedItem(Inventary[knowWhereWeAre_]);

						//Creamos el nuevo objeto
						
						GameComponent* gc2 = new GameComponent();
						gc2->setTextureId(Inventary[knowWhereWeAre_].tx); gc2->setOriPos(position0); gc2->setPosition(position0); gc2->setWidth(45); gc2->setHeight(45);
						gc2->addRenderComponent(new RenderSingleFrameComponent());
						gc2->setColFrame(Inventary[knowWhereWeAre_].colFrame); gc2->setRowFrame(Inventary[knowWhereWeAre_].FilFrame);

						bag->stageBack(gc2);
						bag->pushEquipedItem(Inventary[knowWhereWeAre_]);
						
						}
					
					else {
						Vector2D position1(5.8, 9.7);
						Inventary[knowWhereWeAre_].equiped = true;
						bag->pushEItem();

						//Creamos el nuevo objeto

						GameComponent* gc2 = new GameComponent();
						gc2->setTextureId(Inventary[knowWhereWeAre_].tx); gc2->setOriPos(position1); gc2->setPosition(position1); gc2->setWidth(45); gc2->setHeight(45);
						gc2->addRenderComponent(new RenderSingleFrameComponent());
						gc2->setColFrame(Inventary[knowWhereWeAre_].colFrame); gc2->setRowFrame(Inventary[knowWhereWeAre_].FilFrame);

						bag->stageBack(gc2);
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

				
			}
		}

		else if (XboxController::Instance()->getButtonState(0, 2)) {

			vector<estado> sp = bag->getSP();
			vector<estado> Inventary = bag->getInvent();
			for each (estado S in bag->getEquipedItems())
			{

				bag->pullEitem();
				bag->setLeft(false);
				isLeft = false;
				bool found = false;
				for (int i = 0; i < Inventary.size() && !found; i++) {
					if (S.ID == Inventary[i].ID) {
						Inventary[i].equiped = false;
						found = true;
					}
				}
			}
				
			bag->pullEquipedItem();

			GameManager::Instance()->changeInventory(Inventary);
			bag->setInvent(Inventary);
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

