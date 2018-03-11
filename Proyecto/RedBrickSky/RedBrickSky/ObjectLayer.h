#pragma once

#include <iostream>
#include <vector>

#include "Layer.h"
#include "CollisionManager.h"

class GameObject;

class ObjectLayer :	public Layer
{
public:
	virtual ~ObjectLayer();

	virtual void update(Level* pLevel);
	virtual void render();

	std::vector<GameObject*>* getGameObjects() { return &m_gameObjects; }

private:
	CollisionManager m_collisionManager;		// gestor de colisiones con el mapa
	std::vector<GameObject*> m_gameObjects;		// objetos del nivel
};

