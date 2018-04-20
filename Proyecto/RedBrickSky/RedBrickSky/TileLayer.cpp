#include "TileLayer.h"
#include "Game.h"
#include "TextureManager.h"
#include "Camera.h"

TileLayer::TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset>& tilesets, int dID) :
	m_tileSize(tileSize), m_tilesets(tilesets), m_position(0, 0), doorID(dID)
{
	m_numColumns = mapWidth;
	m_numRows = mapHeight;

	m_mapWidth = mapWidth;

	active_ = false;
}

void TileLayer::update(Level* pLevel)
{
}

void TileLayer::render()
{
	if (!active_) return;

	// calculamos la posición relativa de la capa
	int x, y, x2, y2 = 0;
	x = m_position.getX() / m_tileSize;
	y = m_position.getY() / m_tileSize;
	x2 = int(m_position.getX()) % m_tileSize;
	y2 = int(m_position.getY()) % m_tileSize;

	// renderizamos todos los tiles de la capa
	for (int i = 0; i < m_numRows; i++)
	{
		for (int j = 0; j < m_numColumns; j++)
		{
			// obtenemos la ID del tile que queremos renderizar
			int id = m_tileIDs[i + y][j + x];//0
			if (id == 0) continue;

			if (((j * m_tileSize) - x2) - TheCamera::Instance()->getPosition().getX() < -m_tileSize || 
				((j * m_tileSize) - x2) - TheCamera::Instance()->getPosition().getX() > TheGame::Instance()->getWinWidth())
			{
				continue;
			}

			Tileset tileset = getTilesetByID(id);
			id--;

			// lo renderizamos
			TheTextureManager::Instance()->drawTile(tileset.name, tileset.margin, tileset.spacing,
				((j * m_tileSize) - x2) - TheCamera::Instance()->getPosition().getX(), 
				((i * m_tileSize) - y2) - TheCamera::Instance()->getPosition().getY(), 
				m_tileSize, m_tileSize,
				(id - (tileset.firstGridID - 1)) / tileset.numColumns,
				(id - (tileset.firstGridID - 1)) % tileset.numColumns, 
				Game::Instance()->getRenderer());
		}
	}
}

Tileset TileLayer::getTilesetByID(int tileID)
{
	for (int i = 0; i < m_tilesets.size(); i++)
	{
		if (i + 1 <= m_tilesets.size() - 1)
		{
			if (tileID >= m_tilesets[i].firstGridID&&tileID < m_tilesets[i + 1].firstGridID)
			{
				return m_tilesets[i];
			}
		}
		else
		{
			return m_tilesets[i];
		}
	}
	std::cout << "did not find tileset, returning empty tileset\n";
	Tileset t;
	return t;
}
