#pragma once
#include "GameState.h"
#include "RenderFullComponent.h"
#include "RenderSingleFrameComponent.h"
#include "MouseScrollComponent.h"
#include "MouseOverObjectComponent.h"
#include "StateMachine.h"
#include "MouseInputComponentButton.h"
#include "DragNDropShopComponent.h"
#include "MouseInfoClickComponent.h"
#include "GameComponent.h"
#include "Button.h"
#include <vector>

#include "GameManager.h"
#include "checkML.h"

class BackPack : public GameState
{
private:

	//COMPONENTES NECESARIOS
	RenderComponent* rcF; //Render Frame
	RenderComponent* rc; //Render FS
	RenderComponent* rcSF;
	InputComponent* MSC;
	InputComponent* MSOC;
	InputComponent* MIC;
	InputComponent* DND;
	InputComponent* DND2;
	InputComponent* Info;

	int money;

	vector<estado> invent;
	vector<estado> SP;
	vector<GameObject*> StandPointsO;
	
	vector<GameComponent*> botones;

	//Vectores para los distintos tipos de objetos
	vector<estado> Weapons; //Vector para las armas
	vector<estado> Potions; //Vector para las pociones
	vector<estado> Objects; //Vector para los objetos
	vector<estado> EquipedItems; //Vector para los objetos equipados

	vector<estado> GCInventV;

	estado** matriz;
	int numFils = 3;
	int numRows = 4;

	int ocupados;
	int numSP; int actFilas;
	int ultimaFilaY;

	int EItems;

	bool buttonsCreated;

	GameComponent* selector_;

public:
	BackPack();
	virtual ~BackPack();


	virtual bool handleEvent(const SDL_Event& event);

    static void toMenu();
	vector<estado> getSP() { return SP; };
	vector<estado> getInvent() { return invent; };
	void setInvent(vector<estado> v);
	void setSP(vector<estado> v);
	void cargaElementos(vector<estado> l);
	void elimina();
	void creaSP();
	void creaEscena();
	void creaFondoTienda();
	void createButtons(int x, int y, vector<estado> type, std::string t);
	void separateElements();
	void createItemAtSP(int x, int y, int aux, estado st);	
};


