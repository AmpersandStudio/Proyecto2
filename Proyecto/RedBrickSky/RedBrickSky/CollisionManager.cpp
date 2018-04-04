#include "CollisionManager.h"
#include "Player.h"
#include "TileLayer.h"
#include "StateMachine.h"
#include "PlayState.h"

void CollisionManager::checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers)
{

		if (checkCollision(pPlayer, collisionLayers) != 0)
		{
			pPlayer->collision();
		}
}

void CollisionManager::checkPlayerGrassCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers)
{
	if (checkCollision(pPlayer, collisionLayers) != 0 && pPlayer->getMoved()){
		GameState* p = Game::Instance()->getStateMachine()->currentState();
		PlayState* play = static_cast<PlayState*>(p);
		play->actSteps();
	}
}

bool CollisionManager::checkCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers) {
	for (std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
	{
		TileLayer* pTileLayer = (*it);
		std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

		Vector2D layerPos = pTileLayer->getPosition();

		int x, y, tileColumn, tileRow, tileid = 0;

		x = layerPos.getX() / pTileLayer->getTileSize();
		y = layerPos.getY() / pTileLayer->getTileSize();

		int pPosX = pPlayer->getPosition().getX();
		int pPosY = pPlayer->getPosition().getY();

		if (pPlayer->getVel().getY() == 0)
		{
			tileRow = ((pPosY + pPlayer->getHeight()) / pTileLayer->getTileSize());

			if (pPlayer->getVel().getX() > 0)
			{
				tileColumn = ((pPosX + pPlayer->getWidth()) / pTileLayer->getTileSize());

			}
			else if (pPlayer->getVel().getX() < 0)
			{
				tileColumn = pPosX / pTileLayer->getTileSize();
			}
			else if (pPlayer->getVel().getX() == 0)
			{
				tileColumn = ((pPosX + (pPlayer->getWidth() / 2)) / pTileLayer->getTileSize());
			}
		}
		else if (pPlayer->getVel().getY() > 0)
		{
			tileRow = ((pPosY + pPlayer->getHeight()) / pTileLayer->getTileSize());

			if (pPlayer->getVel().getX() > 0)
			{
				tileColumn = ((pPosX + pPlayer->getWidth()) / pTileLayer->getTileSize());

			}
			else if (pPlayer->getVel().getX() < 0)
			{
				tileColumn = pPosX / pTileLayer->getTileSize();
			}
			else if (pPlayer->getVel().getX() == 0)
			{
				tileColumn = ((pPosX + (pPlayer->getWidth() / 2)) / pTileLayer->getTileSize());
			}
		}
		else if (pPlayer->getVel().getY() < 0)
		{
			tileRow = ((pPosY + (pPlayer->getHeight() / 2)) / pTileLayer->getTileSize());

			if (pPlayer->getVel().getX() > 0)
			{
				tileColumn = ((pPosX + pPlayer->getWidth()) / pTileLayer->getTileSize());

			}
			else if (pPlayer->getVel().getX() < 0)
			{
				tileColumn = pPosX / pTileLayer->getTileSize();
			}
			else if (pPlayer->getVel().getX() == 0)
			{
				tileColumn = ((pPosX + (pPlayer->getWidth() / 2)) / pTileLayer->getTileSize());
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