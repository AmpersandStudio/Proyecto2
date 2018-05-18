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
			Inventary.clear();
			Inventary = bag->getInvent();

			if (Inventary.size() != 0 && !sp[identifier].empty && !Inventary[identifier].equiped) {

				Inventary[identifier].equiped = true;

				//Si tenemos hueco en los SP del personaje
				if (bag->getEItems() < 2) {

					//Si la casilla izquierda de la mochila está libre
					if (!bag->getLeft()) {
						Vector2D position0(2.6, 9.7);
						Inventary[identifier].equiped = true;
						bag->setLeft(true);
						isLeft = true;
						bag->pushEItem();
						bag->pushEquipedItem(Inventary[identifier]);

						//Creamos el nuevo objeto

						GameComponent* gc2 = new GameComponent();
						gc2->setTextureId(Inventary[identifier].tx); gc2->setOriPos(position0); gc2->setPosition(position0); gc2->setWidth(45); gc2->setHeight(45);
						gc2->addRenderComponent(new RenderSingleFrameComponent());
						gc2->setColFrame(Inventary[identifier].colFrame); gc2->setRowFrame(Inventary[identifier].FilFrame);

						bag->stageBack(gc2);
						bag->pushEquipedItem(Inventary[identifier]);

					}

					else {
						Vector2D position1(5.8, 9.7);
						Inventary[identifier].equiped = true;
						bag->pushEItem();

						//Creamos el nuevo objeto

						GameComponent* gc2 = new GameComponent();
						gc2->setTextureId(Inventary[identifier].tx); gc2->setOriPos(position1); gc2->setPosition(position1); gc2->setWidth(45); gc2->setHeight(45);
						gc2->addRenderComponent(new RenderSingleFrameComponent());
						gc2->setColFrame(Inventary[identifier].colFrame); gc2->setRowFrame(Inventary[identifier].FilFrame);

						bag->stageBack(gc2);
					}

				}

				else {
					Inventary[identifier].equiped = false;
					//Lanzamos un mensaje diciendo que hay que quitar un objeto
					StringToScreen::Instance()->renderBackGround();
					StringToScreen::Instance()->setMessage("¡Desequipa algo! ");
					StringToScreen::Instance()->startMessagin();
				}

				GameManager::Instance()->changeInventory(Inventary);
				bag->setInvent(Inventary);


			}
		}


	}
	else if (event.type == SDL_KEYDOWN && event.button.button == SDLK_BACKSPACE) {

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

	return handledEvent;
}
