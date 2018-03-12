#pragma once

#include <iostream>
#include <vector>

class GameObject;
class TileLayer;
class Player;

class CollisionManager
{
public:
	CollisionManager() {}
	~CollisionManager() {}

	void checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);

};

