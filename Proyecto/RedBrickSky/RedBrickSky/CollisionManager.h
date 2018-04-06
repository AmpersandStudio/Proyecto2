#pragma once

#include <iostream>
#include <vector>

#include "Interactuable.h"
#include "NPC.h"
#include "Cartel.h"
#include "SchoolBag.h"

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

	void checkNPCInteractions(Player * pPlayer, const std::vector<NPC*>& NonPC);

	void checkBagsInteractions(Player* pPlayer, const std::vector<SchoolBag*>&  b);

	bool checkCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);

	void checkPlayerGrassCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);

	void checkCartelesInteractions(Player* pPlayer, const std::vector<Cartel*>&  c);
	

	bool RectRect(SDL_Rect * A, SDL_Rect * B);

};

