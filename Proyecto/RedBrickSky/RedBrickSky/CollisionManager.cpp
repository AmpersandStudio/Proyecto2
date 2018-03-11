#include "CollisionManager.h"
#include "TileLayer.h"

//void CollisionManager::checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers)
//{
//	for (std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
//	{
//		TileLayer* pTileLayer = (*it);
//		std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();
//
//		Vector2D layerPos = pTileLayer->getPosition();
//
//		int x, y, tileColumn, tileRow, tileid = 0;
//
//		x = layerPos.getX() / pTileLayer->getTileSize();
//		y = layerPos.getY() / pTileLayer->getTileSize();
//
//		int pPosX = pPlayer->getPosition().getX();
//		int pPosY = pPlayer->getPosition().getY();
//
//		if (pPlayer->getVelocity().getY() == 0)
//		{
//			tileRow = ((pPosY + pPlayer->getHeight()) / pTileLayer->getTileSize());
//
//			if (pPlayer->getVelocity().getX() > 0)
//			{
//				tileColumn = ((pPosX + pPlayer->getWidth()) / pTileLayer->getTileSize());
//
//			}
//			else if (pPlayer->getVelocity().getX() < 0)
//			{
//				tileColumn = pPosX / pTileLayer->getTileSize();
//			}
//			else if (pPlayer->getVelocity().getX() == 0)
//			{
//				tileColumn = ((pPosX + (pPlayer->getWidth() / 2)) / pTileLayer->getTileSize());
//			}
//		}
//		else if (pPlayer->getVelocity().getY() > 0)
//		{
//			tileRow = ((pPosY + pPlayer->getHeight()) / pTileLayer->getTileSize());
//
//			if (pPlayer->getVelocity().getX() > 0)
//			{
//				tileColumn = ((pPosX + pPlayer->getWidth()) / pTileLayer->getTileSize());
//
//			}
//			else if (pPlayer->getVelocity().getX() < 0)
//			{
//				tileColumn = pPosX / pTileLayer->getTileSize();
//			}
//			else if (pPlayer->getVelocity().getX() == 0)
//			{
//				tileColumn = ((pPosX + (pPlayer->getWidth() / 2)) / pTileLayer->getTileSize());
//			}
//		}
//		else if (pPlayer->getVelocity().getY() < 0)
//		{
//			tileRow = ((pPosY + (pPlayer->getHeight() / 2)) / pTileLayer->getTileSize());
//
//			if (pPlayer->getVelocity().getX() > 0)
//			{
//				tileColumn = ((pPosX + pPlayer->getWidth()) / pTileLayer->getTileSize());
//
//			}
//			else if (pPlayer->getVelocity().getX() < 0)
//			{
//				tileColumn = pPosX / pTileLayer->getTileSize();
//			}
//			else if (pPlayer->getVelocity().getX() == 0)
//			{
//				tileColumn = ((pPosX + (pPlayer->getWidth() / 2)) / pTileLayer->getTileSize());
//			}
//		}
//
//		tileid = tiles[tileRow + y][tileColumn + x];
//
//		if (tileid != 0)
//		{
//			pPlayer->collision();
//		}
//	}
//}
