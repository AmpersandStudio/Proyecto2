#include "ObjectLayer.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Game.h"
#include "Level.h"

ObjectLayer::~ObjectLayer()
{
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		delete (*it);
	}

	m_gameObjects.clear();
}

void ObjectLayer::update(Level* pLevel)
{
	// COLISIONES
	m_collisionManager.checkPlayerTileCollision(pLevel->getPlayer(), pLevel->getCollidableLayers());

	for (GameObject* go : m_gameObjects)
	{
		go->update();
	}
}

void ObjectLayer::render()
{
	for (GameObject* go : m_gameObjects)
	{
		go->render();
	}
}