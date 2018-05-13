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
	if (pLevel->getPlayer()->getMoved()) {
		m_collisionManager.checkPlayerTileCollision(pLevel->getPlayer(), pLevel->getCollidableLayers()); //Colisiones del jugador
		//GRASS
		m_collisionManager.checkPlayerGrassCollision(pLevel->getPlayer(), pLevel->getGrasseableLayers());
		//DOORS
		m_collisionManager.checkPlayerDoorCollision(pLevel->getPlayer(), pLevel->getDoorsInteractions());
	}

	int NPCnumber = pLevel->getNPCs()->size();
	for (int i = 0; i < NPCnumber; i++) {
			
		if (!pLevel->getNPCs()->at(i)->getState()) { //Añadimos una línea para que solo compruebe colisiones mientras se mueve 
			
			//Cabe destacar que la mayor parte del tiempo está parado
			//LA SIGUIENTE LINEA CONSUME CPU
			m_collisionManager.checkNPCTileCollision(pLevel->getNPCs()->at(i), pLevel->getCollidableLayers()); //NPC's con las colisiones

			m_collisionManager.checkNPCDoorCollision(pLevel->getNPCs()->at(i), pLevel->getDoorsInteractions());
				//pLevel->getNPCs()->at(i)->incrementMovCont();
			 //EL SIGUIENTE BUCLE CONSUME CPU
			for (int p = 0; p < NPCnumber; p++) {
				if (p != i)
					m_collisionManager.checkNPCGOinteraction(pLevel->getNPCs()->at(i), pLevel->getNPCs()->at(p)); // NPC's con ellos mismo
			}
		}

		else pLevel->getNPCs()->at(i)->incrementMovCont();

		//Dejamos de todas maneras las colisiones con el player porque no consumian demasiado antes y son necesarias
		m_collisionManager.checkPlayerGOinteraction(pLevel->getNPCs()->at(i), pLevel->getPlayer()); //Npc's con el player

	
	}

	//INTERACCIONES
	if (pLevel->getPlayer()->isInteracting()) {
		m_collisionManager.checkCartelesInteractions(pLevel->getPlayer(), pLevel->getCartelesinteraction());
		m_collisionManager.checkInteractions(pLevel->getPlayer(), pLevel->getInteractuables());
		m_collisionManager.checkNPCInteractions(pLevel->getPlayer(), pLevel->getNPCinteraction());
		m_collisionManager.checkBagsInteractions(pLevel->getPlayer(), pLevel->getBagsInteractions());
	//	m_collisionManager.checkKeysInteractions(pLevel->getPlayer(), pLevel->getKeysInteractions());
		m_collisionManager.checkDoorsInteractions(pLevel->getPlayer(), pLevel->getDoorsInteractions());
	}

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