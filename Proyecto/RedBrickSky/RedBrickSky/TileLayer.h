#pragma once

#include <iostream>
#include <vector>

#include "Layer.h"
#include "Level.h"
#include "Vector2D.h"

#include "checkML.h"

class TileLayer : public Layer
{
public:
	TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset> &tilesets);
	virtual ~TileLayer() {}

	virtual void update(Level* pLevel);
	virtual void render();

	void setTileIDs(const std::vector<std::vector<int>>& data) { m_tileIDs = data; }
	void setTileSize(int tileSize) { m_tileSize = tileSize; }
	void setMapWidth(int mapWidth) { m_mapWidth = mapWidth; }
	int getCols() { return m_numColumns; };
	int getRows() { return m_numRows; };
	int getTileSize() { return m_tileSize; }
	const std::vector<std::vector<int>>& getTileIDs() { return m_tileIDs; }
	const Vector2D getPosition() { return m_position; }
	Tileset getTilesetByID(int tileID);

private:
	int m_numColumns;	// num cols de la capa
	int m_numRows;		// num fils de la capa
	int m_tileSize;		// tamaño de los tiles
	int m_mapWidth;		// ancho de la capa

	Vector2D m_position;	// posicion de la capa

	const std::vector<Tileset> &m_tilesets;		// tilesets de la capa
	std::vector<std::vector<int>> m_tileIDs;	// matriz de IDs de cada tile de la capa
};
