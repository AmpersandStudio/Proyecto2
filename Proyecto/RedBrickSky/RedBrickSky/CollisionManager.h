#pragma once

#include <iostream>
#include <vector>

#include "Interactuable.h"
#include "NPC.h"
#include "Cartel.h"
#include "SchoolBag.h"
#include "Key.h"
#include "Door.h"

#include "checkML.h"

class GameObject;
class TileLayer;
class Player;

class CollisionManager
{
public:
	CollisionManager() {}
	~CollisionManager() {}

	void checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);

	void checkNPCTileCollision(NPC* pPlayer, const std::vector<TileLayer*>& collisionLayers);

	void checkInteractions(Player * pPlayer, const std::vector<Interactuable*>& interactuables);

	void checkNPCInteractions(Player * pPlayer, const std::vector<NPC*>& NonPC);

	void checkBagsInteractions(Player* pPlayer, const std::vector<SchoolBag*>&  b);

	void checkKeysInteractions(Player* pPlayer, std::vector<Key*>&  k);

	bool checkCollision(GameObject* pPlayer, const std::vector<TileLayer*>& collisionLayers);

	void checkPlayerGrassCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);

	void checkPlayerDoorCollision(Player * pPlayer, std::vector<Door*>& d);

	void checkCartelesInteractions(Player* pPlayer, const std::vector<Cartel*>&  c);

	void checkPlayerGOinteraction(NPC* o, Player* p);
	
	void checkNPCGOinteraction(NPC* NPC1, NPC* NPC2);


	bool RectRect(SDL_Rect * A, SDL_Rect * B);

};

