#include "BagXboxControllerComponent.h"



BagXboxControllerComponent::BagXboxControllerComponent(int iniX, int iniY, int col, int fil, int dis, vector<GameObject*> v, BackPack* b, ShopState* s)
{
	X_ = iniX;
	Y_ = iniY;
	col_ = col;
	fil_ = fil;
	distance = dis;
	SP = v;
	back = b;
	shop = s;

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
			}
			o->setPosition(position);
		}
		else if (event.jhat.value & SDL_HAT_DOWN) {

			posY += distance;
			if (posY <= col_ * Y_ + 1) {
				position.setY(posY + 0.7);
				j++;
			}
			o->setPosition(position);
		}
		else if (event.jhat.value & SDL_HAT_RIGHT) {

			posX += distance;
			if (posX <= fil_ + X_ + 1) {
				position.setX(posX + 0.7);
				i++;
			}

			o->setPosition(position);
		}
		else if (event.jhat.value & SDL_HAT_LEFT) {


			posX -= distance;
			if (posX >= X_) {
				position.setX(posX - 0.7);
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

			invent.clear();
			if (back != nullptr)
				invent = back->getInvent();

			if (selection_) {
				o->setColFrame(0);

				invent[savedInvent].x = posX - 9;
				invent[savedInvent].y = posY;
				invent[savedInvent].mX = i;
				invent[savedInvent].mY = j;


				Vector2D pos(posX, posY);
				invent[savedInvent].GC->setPosition(pos);
				invent[savedInvent].GC->setOriPos(pos);
				selection_ = false;

				if (back != nullptr)
					back->setInvent(invent);
			}

			else {
				int  p = 0;
				bool encontrado = false;
				while (p < invent.size() && !encontrado) {

					if (invent[p].mX == i && invent[p].mY == j)
						encontrado = true;
					else
						p++;
				}

				if (encontrado) {
					o->setColFrame(1);
					savedInvent = p;
					selection_ = true;

				}
			}

			//El siguiente bucle Cambia el color del SP en el que estamos y pone los demás normales (CON TECLADO)
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
		else if (XboxController::Instance()->getButtonState(0, 2)) { //Si pulsa la X equiparemos el objeto
		/*	invent.clear();
			if (back != nullptr)
				invent = back->getInvent();*/

			if (selection_) {

				std::cout << "Gola cagaroac" << endl;
			

			/*	if (back != nullptr)
					back->setInvent(invent);*/
			}
		}
		else if (XboxController::Instance()->getButtonState(0, 1)) {
			StateMachine* sm = Game::Instance()->getStateMachine();
			sm->popState();
		}
	}
	else if (event.type == SDL_JOYBUTTONUP)
		XboxController::Instance()->onJoystickButtonUp(event);
	return handledEvent;
}
