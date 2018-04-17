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
	m_collisionManager.checkPlayerTileCollision(pLevel->getPlayer(), pLevel->getCollidableLayers()); //Colisiones del jugador
	int NPCnumber = pLevel->getNPCs()->size();
	for (int i = 0; i < NPCnumber; i++) {

		m_collisionManager.checkNPCTileCollision(pLevel->getNPCs()->at(i), pLevel->getCollidableLayers()); //NPC's con las colisiones
		m_collisionManager.checkPlayerGOinteraction(pLevel->getNPCs()->at(i), pLevel->getPlayer()); //Npc's con el player

		for (int p = 0; p < NPCnumber; p++) {
			if(p != i)
				m_collisionManager.checkNPCGOinteraction(pLevel->getNPCs()->at(i), pLevel->getNPCs()->at(p)); // NPC's con ellos mismo
		}
	}

	//INTERACCIONES
	if (pLevel->getPlayer()->isInteracting()) {
		m_collisionManager.checkInteractions(pLevel->getPlayer(), pLevel->getInteractuables());
		m_collisionManager.checkNPCInteractions(pLevel->getPlayer(), pLevel->getNPCinteraction());
		m_collisionManager.checkCartelesInteractions(pLevel->getPlayer(), pLevel->getCartelesinteraction());
		m_collisionManager.checkBagsInteractions(pLevel->getPlayer(), pLevel->getBagsInteractions());
		m_collisionManager.checkKeysInteractions(pLevel->getPlayer(), pLevel->getKeysInteractions());
	}
	//GRASS
	m_collisionManager.checkPlayerGrassCollision(pLevel->getPlayer(), pLevel->getGrasseableLayers());

	//DOORS 
	m_collisionManager.checkPlayerDoorCollision(pLevel->getPlayer(), pLevel->getDoorLayer());

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