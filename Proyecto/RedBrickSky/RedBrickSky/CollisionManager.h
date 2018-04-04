#pragma once

#include <iostream>
#include <vector>

#include "Interactuable.h"

class GameObject;
class TileLayer;
class Player;

class CollisionManager
{
public:
	CollisionManager() {}
	~CollisionManager() {}

	void checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);

	void checkInteractions(Player * pPlayer, const std::vector<Interactuable*>& interactuables);

	bool checkCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);

	void checkPlayerGrassCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);

	bool RectRect(SDL_Rect * A, SDL_Rect * B);

};

