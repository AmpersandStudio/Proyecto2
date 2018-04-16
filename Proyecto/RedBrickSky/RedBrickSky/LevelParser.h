#pragma once

#include <iostream>
#include <vector>
#include "tinyxml.h"

#include "checkML.h"

class Level;
struct Tileset;
class Layer;
class TileLayer;

class LevelParser
{
public:
	Level* parseLevel(const char* levelFile);

private:
	void parseTextures(TiXmlElement* pTextureRoot);
	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
	void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers, Level* pLevel);
	void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers, std::vector<TileLayer*> *pGrassLayers, std::vector<TileLayer*> *pDoorLayers);

	int m_tileSize;
	int m_width;
	int m_height;

	int zoom;
};

