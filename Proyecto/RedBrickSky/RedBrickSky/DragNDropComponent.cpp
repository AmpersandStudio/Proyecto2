#include "DragNDropComponent.h"

DragNDropComponent::DragNDropComponent(BackPack* b, int id) : bag(b)
{
	isMouseSelection = false;
	identifier = id;
}

DragNDropComponent::~DragNDropComponent()
{
}

bool DragNDropComponent::handleEvent(GameObject* o, const SDL_Event& event) {

	bool handledEvent = false;
	Vector2D position = o->getPosition();
	int x = 0;
	int y = 0;
	SDL_GetMouseState(&x, &y); //comprobamos estado del raton

	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) { //si es evento de raton

		if (x > (position.getX()*o->getWidth()) && x < ((position.getX()*o->getWidth()) + o->getWidth())
			&& y >(position.getY()*o->getHeight()) && y < ((position.getY()*o->getHeight()) + o->getHeight()))
			isMouseSelection = true;
	}

	else if (event.type == SDL_MOUSEMOTION  && isMouseSelection) {

		Vector2D v;
		v.set((x - 38) / (o->getWidth()), (y - 40) / (o->getHeight()));
		o->setPosition(v);
	}

	else  if (event.type == SDL_MOUSEBUTTONUP && isMouseSelection) {
		isMouseSelection = false;

		if (!devMat(x, y, o))
			o->setPosition(o->getOriPos());
	}
	return handledEvent;
}

bool DragNDropComponent::devMat(int x, int y, GameObject* o) {
	bool aceptada = false;

	int auxX;
	int auxY;
	int auxW;
	int auxH;
	int auxMx;
	int auxMy;
	bool encontrado = false;
	Vector2D v;

	Inventary.clear();
	Inventary = GameManager::Instance()->copyInventory();
	StandPoints = bag->getSP();
	unsigned int i = 0;
	while (i < StandPoints.size() && !encontrado) {
		//Busca si el objeto se ha dejado en alguno de los Stand Points
		{
			auxW = StandPoints[i].w;
			auxH = StandPoints[i].h;
			auxX = StandPoints[i].x * auxW;
			auxY = StandPoints[i].y * auxH;
			auxMx = StandPoints[i].mX;
			auxMy = StandPoints[i].mY;

			if (x > (auxX) && x < ((auxX)+auxW) && y >(auxY) && y < ((auxY)+auxH)) {
				encontrado = true;
			}

			else
				i++;
		}
	}

	if (encontrado) {

		if (StandPoints[i].empty) {

			StandPoints[i].ID = identifier;
			StandPoints[i].empty = false;
			double posX, posY;
			posX = auxX + auxW / 2;
			posY = auxY + auxH / 2;
			
			bool found = false;
			for (unsigned int i = 0; i < Inventary.size() && !found; i++) {
				if (Inventary[i].ID == identifier) {
					found = true;
					Inventary[identifier].x = x;
					Inventary[identifier].y = y;
					Inventary[identifier].mX = auxMx;
					Inventary[identifier].mY = auxMy;
				}
			}

			v.set(o->getOriPos().getX(), o->getOriPos().getY());

			if (StandPoints[i].equiped)
			{
				Inventary[identifier].equiped = true;

				if (auxMy == -1) 
					v.set(x / auxW * 1.3, y / auxH * 1.6);
									
				else 
					v.set(x / auxW * 1.4, y / auxH * 1.6);
			
				Inventary[identifier].x = 1.2;
				Inventary[identifier].y = 2.5;

				GameManager::Instance()->changeInventory(Inventary);
				bag->setInvent(Inventary);
				bag->setSP(StandPoints);

			}
			else {
				v.set(posX / 45 - 0.5, posY / 45 - 0.5);
				Inventary[identifier].equiped = false;
				GameManager::Instance()->changeInventory(Inventary);
				bag->setInvent(Inventary);
				bag->setSP(StandPoints);
			}

			o->setPosition(v);
			o->setOriPos(v);
			aceptada = true;

			for (unsigned int p = 0; p < StandPoints.size(); p++)
				StandPoints[p].empty = true;

			for (unsigned int x = 0; x < Inventary.size(); x++) {
				int c = 0;
				bool found = false;
				while (c < StandPoints.size() && !found)
				{

					if (Inventary[x].mX == StandPoints[c].mX && Inventary[x].mY == StandPoints[c].mY) {
						StandPoints[c].empty = false;
						found = true;
					}
					else
						c++;
				}
			}
		}
		else if (!StandPoints[i].empty)
		{
			std::cout << "Pero hombre que ahi ya tienes un arma..." << endl;
		}
	}

	return aceptada;
}

