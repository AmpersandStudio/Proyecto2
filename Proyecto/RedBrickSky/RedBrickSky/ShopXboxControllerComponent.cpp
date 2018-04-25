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

	if (XboxController::Instance()->getNumControllers() == 0) //SOLO UN MANDO
		XboxController::Instance()->insertController();
}


ShopXboxControllerComponent::~ShopXboxControllerComponent()
{

}


bool ShopXboxControllerComponent::handleEvent(GameObject* o, const SDL_Event& event) {
	bool handledEvent = false;

	if (event.type == SDL_JOYHATMOTION) {
		Vector2D position = o->getPosition();
		double posY = position.getY();
		double posX = position.getX();

		if (event.jhat.value & SDL_HAT_UP) {

			if (posY > Y_)
				posY -= distance * 1.5;

			if (posX >= Y_) {
				position.setY(posY);
				j--;
			}
			o->setPosition(position);
		}
		else if (event.jhat.value & SDL_HAT_DOWN) {

			if (posY < Y_ + fil_ - 1)
				posY += distance * 1.5;

			if (posY <= Y_ + fil_) {
				position.setY(posY);
				j++;
			}
			o->setPosition(position);
		}
		else if (event.jhat.value & SDL_HAT_RIGHT) {

			if (posX < X_ + col_ - 1)
				posX += distance / 2;

			if (posX <= X_ + col_ - 1) {
				position.setX(posX);
				i++;
			}

			o->setPosition(position);
		}
		else if (event.jhat.value & SDL_HAT_LEFT) {

			if (posX >= X_)
				posX -= distance / 2;

			if (posX >= X_) {
				position.setX(posX);
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

	 if (XboxController::Instance()->getButtonState(0,0)) { //Si se ha pulsado la A
		
			unsigned int  p = 0;
			bool encontrado = false;
			while (p < shopObjects.size() && !encontrado) {

				if (shopObjects[p].x == posX && shopObjects[p].y == posY )
					encontrado = true;
				else
					p++;
			}

			if (encontrado) {
				std::cout << shopObjects[savedInvent].nombre << endl;
			
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