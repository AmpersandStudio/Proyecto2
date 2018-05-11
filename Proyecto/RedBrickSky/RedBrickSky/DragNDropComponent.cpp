#include "DragNDropComponent.h"

DragNDropComponent::DragNDropComponent(BackPack* b, int id) : bag(b)
{
	isMouseSelection = false;
	identifier = id;
	isLeft = false;
}

DragNDropComponent::~DragNDropComponent()
{
}

bool DragNDropComponent::handleEvent(GameObject* o, const SDL_Event& event) {

	bool handledEvent = false;
	

	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) { //si es evento de raton
		Vector2D position = o->getPosition();
		vector<estado> sp = bag->getSP();
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y); //comprobamos estado del raton

		if (x > (position.getX()*o->getWidth()) && x < ((position.getX()*o->getWidth()) + o->getWidth())
			&& y >(position.getY()*o->getHeight()) && y < ((position.getY()*o->getHeight()) + o->getHeight()))
		{
			//copio el inventario
			Inventary.clear();
			Inventary = GameManager::Instance()->copyInventory();

			//marco el elemento como comprado != comprado
			Inventary[identifier].equiped = !Inventary[identifier].equiped;

			if (Inventary[identifier].equiped) {
				//Si tenemos hueco en los SP del personaje
				if (bag->getEItems() < 2) {
					
					//Si la casilla izquierda de la mochila está libre
					if (!bag->getLeft()) {
						Vector2D position0(2.6, 9.7);
						o->setPosition(position0);
						bag->setLeft(true);
						isLeft = true;
					}
					else {
						Vector2D position1( 5.8, 9.7);
						o->setPosition(position1);
					}
					//Actualizamos la mochila
					bag->pushEItem();

					//Buscamos el SP que hemos dejado atrás, donde estaba el objeto, y le decimos que está vacío
					for (int i = 0; i < sp.size(); i++)
					{
						if (sp[i].ID == identifier) {
							sp[i].empty = true;
						
						}
					}
				}
				
				else {
					Inventary[identifier].equiped = false;
					//Lanzamos un mensaje diciendo que hay que quitar un objeto
					StringToScreen::Instance()->renderBackGround();
					StringToScreen::Instance()->setMessage("¡Desequipa algo! ");
					StringToScreen::Instance()->startMessagin();
				}
				
			}

			else {
				//Si está !equiped, lo ponemos en un lugar vacío en los SP
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
						o->setPosition(p);//createItemAtSP(x, y, auxV[p].objectID, auxV[p]);
						sp[aux].empty = false;
						place = true;
						identifier = sp[aux].ID;
					}
					else {
						j++;
						aux++;
					}
				}
			}

			GameManager::Instance()->changeInventory(Inventary);
			bag->setInvent(Inventary);
			bag->setSP(sp);

		}
	}

	return handledEvent;
}
