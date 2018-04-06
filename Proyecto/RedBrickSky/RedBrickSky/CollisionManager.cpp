#include "CollisionManager.h"
#include "Player.h"
#include "TileLayer.h"
#include "StateMachine.h"
#include "PlayState.h"
#include "Collisions.h"


void CollisionManager::checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers)
{

		if (checkCollision(pPlayer, collisionLayers) != 0)
		{
			pPlayer->collision();
		}
}

void CollisionManager::checkNPCTileCollision(NPC* pNPC, const std::vector<TileLayer*>& collisionLayers) {
	if (checkCollision(pNPC, collisionLayers) != 0)
	{
		pNPC->collision();
	}
	else
		pNPC->incrementMovCont();
}

void CollisionManager::checkPlayerGrassCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers)
{
	if (checkCollision(pPlayer, collisionLayers) != 0 && pPlayer->getMoved()){
		GameState* p = Game::Instance()->getStateMachine()->currentState();
		PlayState* play = static_cast<PlayState*>(p);
		play->actSteps();
	}

	else if (pPlayer->getMoved()) {
		GameState* p = Game::Instance()->getStateMachine()->currentState();
		PlayState* play = static_cast<PlayState*>(p);
		play->notOnGrass();
	}
}

bool CollisionManager::checkCollision(GameObject* o, const std::vector<TileLayer*>& collisionLayers) {
	for (std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
	{
		TileLayer* pTileLayer = (*it);
		std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

		Vector2D layerPos = pTileLayer->getPosition();

		int x, y, tileColumn, tileRow, tileid = 0;

		x = layerPos.getX() / pTileLayer->getTileSize();
		y = layerPos.getY() / pTileLayer->getTileSize();

		int pPosX = o->getPosition().getX();
		int pPosY = o->getPosition().getY();

		if (o->getVel().getY() == 0)
		{
			tileRow = ((pPosY + o->getHeight()) / pTileLayer->getTileSize());

			if (o->getVel().getX() > 0)
			{
				tileColumn = ((pPosX + o->getWidth()) / pTileLayer->getTileSize());

			}
			else if (o->getVel().getX() < 0)
			{
				tileColumn = pPosX / pTileLayer->getTileSize();
			}
			else if (o->getVel().getX() == 0)
			{
				tileColumn = ((pPosX + (o->getWidth() / 2)) / pTileLayer->getTileSize());
			}
		}
		else if (o->getVel().getY() > 0)
		{
			tileRow = ((pPosY + o->getHeight()) / pTileLayer->getTileSize());

			if (o->getVel().getX() > 0)
			{
				tileColumn = ((pPosX + o->getWidth()) / pTileLayer->getTileSize());

			}
			else if (o->getVel().getX() < 0)
			{
				tileColumn = pPosX / pTileLayer->getTileSize();
			}
			else if (o->getVel().getX() == 0)
			{
				tileColumn = ((pPosX + (o->getWidth() / 2)) / pTileLayer->getTileSize());
			}
		}
		else if (o->getVel().getY() < 0)
		{
			tileRow = ((pPosY + (o->getHeight() / 2)) / pTileLayer->getTileSize());

			if (o->getVel().getX() > 0)
			{
				tileColumn = ((pPosX + o->getWidth()) / pTileLayer->getTileSize());

			}
			else if (o->getVel().getX() < 0)
			{
				tileColumn = pPosX / pTileLayer->getTileSize();
			}
			else if (o->getVel().getX() == 0)
			{
				tileColumn = ((pPosX + (o->getWidth() / 2)) / pTileLayer->getTileSize());
			}
		}

		return(tiles[tileRow + y][tileColumn + x]);
	}
}

void CollisionManager::checkInteractions(Player* pPlayer, const std::vector<Interactuable*>& interactuables)
{
	SDL_Rect* playerRect = pPlayer->getRect();

	for (Interactuable* i : interactuables)
	{
		SDL_Rect* interRect = i->getRect();

		if (RectRect(playerRect, interRect))
		{
			i->activate();
		}
	}

	pPlayer->setInteracting(false);
}

void CollisionManager::checkPlayerGOinteraction(NPC* o, Player* player) {
	
	/*if (Collisions::collides(o, player)) {
		Vector2D oPos = o->getPosition();
		Vector2D oDir = o->getDirection();
		
		double odirX = -2 * oDir.getX();
		double odirY = -2 * oDir.getY();

		double ox = odirX + oPos.getX();
		double oy = odirY + oPos.getY();

		oPos.set(ox, oy);

		Vector2D pPos = player->getPosition();
		Vector2D pDir = player->getDirection();

		double pdirX = -2 * pDir.getX();
		double pdirY = -2 * pDir.getY();

		double px = pdirX + pPos.getX();
		double py = pdirY + pPos.getY();

		pPos.set(px, py);

		player->setPosition(pPos);
		o->setPosition(oPos);

		player->collision();
		o->collision();
	}*/

}


void CollisionManager::checkNPCInteractions(Player* pPlayer, const std::vector<NPC*>&  NonPC)
{
	SDL_Rect* playerRect = pPlayer->getRect();

	for (NPC* i : NonPC)
	{
		SDL_Rect* interRect = i->getRect();

		if (RectRect(playerRect, interRect))
		{
			i->activate();
		}
	}

	pPlayer->setInteracting(false);
}

void CollisionManager::checkBagsInteractions(Player* pPlayer, const std::vector<SchoolBag*>&  b)
{
	SDL_Rect* playerRect = pPlayer->getRect();

	for (SchoolBag* i : b)
	{
		SDL_Rect* interRect = i->getRect();

		if (RectRect(playerRect, interRect))
		{
			i->activate();
		}
	}

	pPlayer->setInteracting(false);
}

void CollisionManager::checkCartelesInteractions(Player* pPlayer, const std::vector<Cartel*>&  c)
{
	SDL_Rect* playerRect = pPlayer->getRect();

	for (Cartel* i : c)
	{
		SDL_Rect* interRect = i->getRect();

		if (RectRect(playerRect, interRect))
		{
			i->activate();
		}
	}

	pPlayer->setInteracting(false);
}


bool CollisionManager::RectRect(SDL_Rect* A, SDL_Rect* B)
{
	// if the bottom of A is less than the top of B - no collision
	if ((A->y + A->h) <= B->y) { return false; }

	// if the top of A is more than the bottom of B = no collision
	if (A->y >= (B->y + B->h)) { return false; }

	// if the right of A is less than the left of B - no collision
	if ((A->x + A->w) <= B->x) { return false; }

	// if the left of A is more than the right of B - no collision
	if (A->x >= (B->x + B->w)) { return false; }

	// otherwise there has been a collision
	return true;
}