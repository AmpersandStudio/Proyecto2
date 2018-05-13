#include "CollisionManager.h"
#include "Player.h"
#include "TileLayer.h"
#include "StateMachine.h"
#include "PlayState.h"
#include "Collisions.h"
#include <typeinfo>

void CollisionManager::checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers)
{

		if (checkCollision(pPlayer, collisionLayers) != 0)
		{
			TheSoundManager::Instance()->playSound("rebote", 0);

			Vector2D pPos = pPlayer->getPosition();
			Vector2D pDir = pPlayer->getDirection();

			double pdirX = -5 * pDir.getX();
			double pdirY = -5 * pDir.getY();

			double px = pdirX + pPos.getX();
			double py = pdirY + pPos.getY();

			pPos.set(px, py);

			pPlayer->setPosition(pPos);
			pPlayer->collision();
		}
}

void CollisionManager::checkNPCTileCollision(NPC* pNPC, const std::vector<TileLayer*>& collisionLayers) {

		int aux = checkCollision(pNPC, collisionLayers);
		if (!pNPC->getState() && aux != 0)
		{
			if (aux == -1)
				pNPC->invertVel();
			else
			{
				Vector2D pPos = pNPC->getPosition();
				Vector2D pDir = pNPC->getVel();

				double pdirX = -5 * pDir.getX();
				double pdirY = -5 * pDir.getY();

				double px = pdirX + pPos.getX();
				double py = pdirY + pPos.getY();

				pPos.set(px, py);

				pNPC->setVel(pDir * -1);
				pNPC->invertVel();
				pNPC->setPosition(pPos);

				pNPC->collision();
			}
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

void CollisionManager::checkPlayerDoorCollision(Player * pPlayer, std::vector<Door*>& d)
{
	SDL_Rect* playerRect = pPlayer->getRect();

	bool activated = false;
	for (Door* door : d)
	{
		if (door->isActive()) continue;

		SDL_Rect* interRect = door->getRect();

		if (Collisions::collides(pPlayer, door))
		{
			TheSoundManager::Instance()->playSound("rebote", 0);

			Vector2D pPos = pPlayer->getPosition();
			Vector2D pDir = pPlayer->getDirection();

			double pdirX = -5 * pDir.getX();
			double pdirY = -5 * pDir.getY();

			double px = pdirX + pPos.getX();
			double py = pdirY + pPos.getY();

			pPos.set(px, py);

			pPlayer->setPosition(pPos);
			pPlayer->collision();
		
		}
	}

	pPlayer->setInteracting(false);
}

void CollisionManager::checkNPCDoorCollision(NPC * NPC, std::vector<Door*>& d)
{
	for (Door* door : d)
	{
		if (door->isActive()) continue;

		if (Collisions::collides(NPC, door)) {

			Vector2D pPos = NPC->getPosition();
			Vector2D pDir = NPC->getVel();

			double pdirX = -5 * pDir.getX();
			double pdirY = -5 * pDir.getY();

			double px = pdirX + pPos.getX();
			double py = pdirY + pPos.getY();

			pPos.set(px, py);

			NPC->setVel(pDir * -1);
			NPC->invertVel();
			NPC->setPosition(pPos);

			NPC->collision();
		}
	}
}


bool CollisionManager::checkCollision(GameObject* o, const std::vector<TileLayer*>& collisionLayers) {
	
	/*Vector2D oriPos = o->getPosition();
	Vector2D v = oriPos + o->getVel();
	v.setX(v.getX() + 2);
	v.setY(v.getY() + 2);

	o->setPosition(v);*/

	for (std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
	{
		TileLayer* pTileLayer = (*it);
		std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();
		int cols = (*it)->getCols();
		int rows = (*it)->getRows();
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

		/*o->setPosition(oriPos);*/

		if (tileRow < 0) { tileRow = 0; return -1; }
		else if (tileRow > rows - 1) { tileRow = rows - 1; return -1; }
		if (tileColumn < 0) { tileColumn = 0; return -1;}
		else if (tileColumn > cols - 1) { tileColumn = cols - 1;  return -1; }
		return(tiles[tileRow + y][tileColumn + x]);
	}

	return false;
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
			break;
		}
	}

	pPlayer->setInteracting(false);
}

void CollisionManager::checkNPCGOinteraction(NPC* NPC1, NPC* NPC2) {

	Vector2D oriPos = NPC1->getPosition();
	Vector2D v = oriPos + NPC1->getVel();
	v.setX(v.getX() + 2);
	v.setY(v.getY() + 2);
	NPC1->setPosition(v);

	if (Collisions::collides(NPC1, NPC2)) {

		Vector2D pPos = NPC1->getPosition();
		Vector2D pDir = NPC1->getDirection();

		double pdirX = -5 * pDir.getX();
		double pdirY = -5 * pDir.getY();

		double px = pdirX + pPos.getX();
		px -= NPC1->getVel().getX();
		double py = pdirY + pPos.getY();
		py = NPC1->getVel().getY();

		pPos.set(px, py);

		NPC1->setPosition(pPos);
		NPC1->collision();
		NPC2->setCollided(true);

	}
	NPC1->setPosition(oriPos);
}

void CollisionManager::checkPlayerGOinteraction(NPC* o, Player* player) {

	Vector2D oriPos = o->getPosition();
	Vector2D v = oriPos + o->getVel();
	
	o->setPosition(v);

	if (Collisions::collides(o, player)) {

		TheSoundManager::Instance()->playSound("rebote", 0);

		Vector2D pPos = player->getPosition();
		Vector2D pDir = player->getDirection();

		double pdirX = -5 * pDir.getX();
		double pdirY = -5 * pDir.getY();

		double px = pdirX + pPos.getX();
		double py = pdirY + pPos.getY();

		pPos.set(px, py);

		player->setPosition(pPos);		
		player->collision();
		o->setCollided(true);

	
			if (pdirY < 0)
			{
				o->setRowFrame(3);
			}
			else if (pdirY > 0)
			{
				o->setRowFrame(0);
			}
			else if (pdirY == 0)
			{
				if (pdirX < 0)
					o->setRowFrame(1);
				else 
					o->setRowFrame(2);
			}

			o->setColFrame(1);
		}
	o->setPosition(oriPos);
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
			break;
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
			break;
		}
	}

	pPlayer->setInteracting(false);
}

void CollisionManager::checkDoorsInteractions(Player* pPlayer, const std::vector<Door*>&  d)
{
	SDL_Rect* playerRect = pPlayer->getRect();

	for (Door* i : d)
	{
		SDL_Rect* interRect = i->getRect();

		if (RectRect(playerRect, interRect))
		{
			i->activate();
			break;
		}
	}

	pPlayer->setInteracting(false);
}

/*void CollisionManager::checkKeysInteractions(Player* pPlayer, std::vector<Key*>&  k)
{
	SDL_Rect* playerRect = pPlayer->getRect();

	int i = 0;
	int aux;
	bool activated = false;
	for (Key* key : k)
	{
		SDL_Rect* interRect = key->getRect();

		if (RectRect(playerRect, interRect))
		{
				key->activate();
				activated = true;
				aux = i;

				std::cout << "HYEYO YOAJYSIJ " << std::endl;

				estado n;
				n.price = 0;
				n.comprado = false;
				n.ID = 0;
				n.empty = false;
				n.objects = 0;
				n.x = 0;
				n.y = 0;
				n.mX = -10;
				n.mY = -10;
				n.w = 50;
				n.h = 50;
				n.tx = "Key";
				n.type = 2;
				n.nombre = "LLave";
				n.FilFrame = 0;
				n.colFrame = 0;

				GameManager::Instance()->setInventory(n);
		}
		i++;
	}

	if (activated)
		k.erase(k.begin() + aux);

	pPlayer->setInteracting(false);
}*/

void CollisionManager::checkCartelesInteractions(Player* pPlayer, const std::vector<Cartel*>&  c)
{
	SDL_Rect* playerRect = pPlayer->getRect();

	bool interacted = false;
	for (Cartel* i : c)
	{
		SDL_Rect* interRect = i->getRect();

		if (RectRect(playerRect, interRect))
		{
				i->activate();
				break;
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