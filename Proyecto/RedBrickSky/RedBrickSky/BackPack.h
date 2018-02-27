#pragma once
#include "GameState.h"
#include "RenderFullComponent.h"
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

class BackPack :
	public GameState
{
private:
	//TEXTURAS NECESARIAS
	Texture* back;
	Texture* standPoint;
	Texture* front;
	Texture* bot;
	Texture* food;
	Texture* food2;

	//COMPONENTES NECESARIOS
	RenderComponent* rcF; //Render Frame
	RenderComponent* rc; //Render FS
	InputComponent* MSC;
	InputComponent* MSOC;
	InputComponent* MIC;
	InputComponent* DND;
	InputComponent* DND2;
	InputComponent* Info;

	Game* game;
	int money;

	vector<estado> invent;
	vector<estado> SP;
	vector<GameComponent*> GCshopV;
	vector<GameComponent*> GCInventV;
	estado** matriz;
	int ocupados;
	int numSP; int actFilas;
	int ultimaFilaY;

public:
	BackPack(Game* gamePtr);
	virtual ~BackPack();
    static void toMenu(Game* game);
	vector<estado> getSP() { return SP; };
};

