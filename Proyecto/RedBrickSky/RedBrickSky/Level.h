#pragma once

#include <string>
#include <vector>

#include "Layer.h"
#include "LevelParser.h"
#include "Player.h"
#include "CollisionManager.h"
#include "Interactuable.h"
#include "NPC.h"
#include "SchoolBag.h"

#include "checkML.h"

class TileLayer;

struct Tileset {
	int firstGridID;	// identificador
	int tileWidth;		// ancho de tile
	int tileHeight;		// alto de tile
	int spacing;		// espacio entre tiles
	int margin;			// margen del tileset
	int width;			// ancho del tileset
	int height;			// alto del tileset
	int numColumns;		// num de cols del tileset
	std::string name;	// nombre del tileset
};

class Level
{
public:
	~Level();

	void update();
	void render();

	std::vector<Tileset>* getTilesets() { return &m_tilesets; }
	std::vector<Layer*>* getLayers() { return &m_layers; }

	std::vector<TileLayer*>* getCollisionLayers() { return &m_collisionLayers; }
	const std::vector<TileLayer*>& getCollidableLayers() { return m_collisionLayers; }

	std::vector<Interactuable*>* getInteractions() { return &m_interactuables; }
	const std::vector<Interactuable*>& getInteractuables() { return m_interactuables; }

	std::vector<NPC*>* getNPCs() { return &m_NPCs; }
	const std::vector<NPC*>& getNPCinteraction() { return m_NPCs; }

	std::vector<Cartel*>* getCarteles() { return &m_Carteles; }
	const std::vector<Cartel*>& getCartelesinteraction() { return m_Carteles; }

	std::vector<SchoolBag*>* getBags() { return &m_Bags; }
	const std::vector<SchoolBag*>& getBagsInteractions() { return m_Bags; }

	std::vector<TileLayer*>* getGrassLayers() { return &m_grassLayer; }
	const std::vector<TileLayer*>& getGrasseableLayers() { return m_grassLayer; }

	std::vector<TileLayer*>* getDoorLayers() { return &m_doorLayer; }
	std::vector<TileLayer*>& getDoorLayer() { return m_doorLayer; }

	Player* getPlayer() { return m_pPlayer; }
	void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	void setTilewidth(int w) { m_tileWidth = w; }
	void setTileheight(int h) { m_tileHeight = h; }

	int getTileWidth() {};

private:
	friend class LevelParser;	// solo podemos crear un nivel desde LevelParser
	Level();

	std::vector<Tileset> m_tilesets;	// tilesets del nivel
	std::vector<Layer*> m_layers;	// capas del nivel
	std::vector<TileLayer*> m_collisionLayers;	// capas de colisiones del nivel
	std::vector<Interactuable*> m_interactuables;
	std::vector<TileLayer*> m_grassLayer; // capa para la hierba alta
	std::vector<TileLayer*> m_doorLayer; // capa para las puertas
	std::vector<NPC*> m_NPCs; //vector de NPC's
	std::vector<Cartel*> m_Carteles; //vector de carteles
	std::vector<SchoolBag*> m_Bags; //vector de Mochilas

	int m_tileWidth;	// ancho de tile del nivel
	int m_tileHeight;	// alto de tile del nivel

	Player* m_pPlayer;
};

