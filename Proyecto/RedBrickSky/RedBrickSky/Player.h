#pragma once

#include "GameObject.h"
#include "GameObjectFactory.h"

class Player : public GameObject
{
public:
	Player(Vector2D position, int width, int height, string textureId, int numFrames, int callbackID = 0, int animSpeed = 0);
	virtual ~Player();

	virtual void render();
	virtual void update();
	virtual bool handleEvent(const SDL_Event& event);

	virtual void collision();
	virtual string type() { return "Player"; };
	
private:
	void handleAnimation();
	void handleInput();
};

// NCM: para utilizar la GameObjectFactory, necesitamos eliminar los punteros a Game
// de la constructora de GameObject; si no, es imposible hacer constructoras base
// sin parametros. La idea es llevar la carga de parametros a un metodo load que se 
// llame posteriormente o desde la propia constructora.

//class PlayerCreator : public BaseCreator
//{
//	GameObject* createGameObject() const
//	{
//		return new Player();
//	}
//};