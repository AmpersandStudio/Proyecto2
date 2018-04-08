#include <string>
#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "ObjectLayer.h"
#include "TileLayer.h"
#include "GameObjectFactory.h"
#include "base64.h"
#include "zlib.h"
#include "Level.h"
#include "Camera.h"

Level* LevelParser::parseLevel(const char *levelFile)
{
	// create a tinyXML document and load the map xml
	TiXmlDocument levelDocument;
	levelDocument.LoadFile(levelFile);

	// create the level object
	Level* pLevel = new Level();

	// get the root node and display some values
	TiXmlElement* pRoot = levelDocument.RootElement();
	std::cout << "Loading level:\n" << "Version: " << pRoot->Attribute("version") << "\n";
	std::cout << "Width:" << pRoot->Attribute("width") << " - Height:" << pRoot->Attribute("height") << "\n";
	std::cout << "Tile Width:" << pRoot->Attribute("tilewidth") << " - Tile Height:" << pRoot->Attribute("tileheight") << "\n";

	pRoot->Attribute("tilewidth", &m_tileSize);
	pRoot->Attribute("width", &m_width);
	pRoot->Attribute("height", &m_height);

	// set the camera limits
	TheCamera::Instance()->setMapDims(m_tileSize * m_width, m_tileSize * m_height);

	//we know that properties is the first child of the root
	TiXmlElement* pProperties = pRoot->FirstChildElement();

	// we must parse the textures needed for this level, which have been added to properties
	for (TiXmlElement* e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("property"))
		{
			parseTextures(e);
		}
	}

	// we must now parse the tilesets
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			parseTilesets(e, pLevel->getTilesets());
		}
	}

	// parse any object layers
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
		{
			if (e->FirstChildElement()->Value() == std::string("object"))
			{
				parseObjectLayer(e, pLevel->getLayers(), pLevel);
			}
			else if (e->FirstChildElement()->Value() == std::string("data") || (e->FirstChildElement()->NextSiblingElement() != 0 && e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data")))
			{
				parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets(), pLevel->getCollisionLayers(), pLevel->getGrassLayers());
			}
		}
	}

	return pLevel;
}


void LevelParser::parseTextures(TiXmlElement* pTextureRoot)
{
	// agrega al Texture Manager las texturas de objetos necesarias
	std::cout << "adding texture " << pTextureRoot->Attribute("value") << " with ID " << pTextureRoot->Attribute("name") << std::endl;
	TheTextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"), TheGame::Instance()->getRenderer());
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
	// first add the tileset to texture manager
	std::string assetsTag = "assets/";
	std::cout << "adding texture " << pTilesetRoot->FirstChildElement()->Attribute("source") << " with ID " << pTilesetRoot->Attribute("name") << std::endl;
	TheTextureManager::Instance()->load(assetsTag.append(pTilesetRoot->FirstChildElement()->Attribute("source")), pTilesetRoot->Attribute("name"), TheGame::Instance()->getRenderer());

	// create a tileset object
	Tileset tileset;
	tileset.margin = tileset.spacing = 0;
	pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
	pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
	pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
	pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
	pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
	pTilesetRoot->Attribute("spacing", &tileset.spacing);
	pTilesetRoot->Attribute("margin", &tileset.margin);
	tileset.name = pTilesetRoot->Attribute("name");
	tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

	pTilesets->push_back(tileset);
}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers, Level* pLevel)
{
	// create an object layer
	ObjectLayer* pObjectLayer = new ObjectLayer();

	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("object"))
		{
			int x = 0, y = 0, width = 32, height = 32, numFrames = 1, callbackID = 0, animSpeed = 0, Sweeties = 0;
			std::string textureID = "000";
			std::string type = "Interactuable";
			std::string Message = " ";
			

			// get the initial node values type, x and y
			e->Attribute("x", &x);
			e->Attribute("y", &y);
			type = e->Attribute("type");

			GameObject* pGameObject = TheGameObjectFactory::Instance()->create(type);

			// get the property values
			for (TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
			{
				if (properties->Value() == std::string("properties"))
				{
					for (TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
					{
						if (property->Value() == std::string("property"))
						{
							if (property->Attribute("name") == std::string("numFrames"))
							{
								property->Attribute("value", &numFrames);
							}
							else if (property->Attribute("name") == std::string("textureHeight"))
							{
								property->Attribute("value", &height);
							}
							else if (property->Attribute("name") == std::string("textureID"))
							{
								textureID = property->Attribute("value");
							}
							else if (property->Attribute("name") == std::string("textureWidth"))
							{
								property->Attribute("value", &width);
							}
							else if (property->Attribute("name") == std::string("callbackID"))
							{
								property->Attribute("value", &callbackID);
							}
							else if (e->Attribute("name") == std::string("animSpeed"))
							{
								property->Attribute("value", &animSpeed);
							}
							else if (property->Attribute("name") == std::string("Message"))
							{
								Message = property->Attribute("value");
							}

							else if (property->Attribute("name") == std::string("Sweeties"))
							{
								property->Attribute("value", &Sweeties);
							}
						}
					}
				}
			}

			pGameObject->load(Vector2D(x, y), width, height, textureID, numFrames, callbackID, animSpeed);

			if (type == "Player")
			{
				pLevel->setPlayer(static_cast<Player*>(pGameObject));
			}

			if (type == "Interactuable")
			{
				pLevel->getInteractions()->push_back(static_cast<Interactuable*>(pGameObject));
			}

			if (type == "NPC")
			{
				NPC* c = static_cast<NPC*>(pGameObject);
				c->setLevel(pLevel);
				c->setMSG(Message);
				c->setTileWidth(m_tileSize * m_width);
				c->setTileHeight(m_tileSize * m_height);

				pLevel->getNPCs()->push_back(c);	
				//pLevel->getNPCs()->push_back(static_cast<NPC*>(pGameObject));
			}


			if (type == "Cartel")
			{
				Cartel* c = static_cast<Cartel*>(pGameObject);
				c->setMessage(Message);
				pLevel->getCarteles()->push_back(c);				

			}

			if (type == "Bag")
			{
				SchoolBag* c = static_cast<SchoolBag*>(pGameObject);
				c->setSweeties(Sweeties);
				pLevel->getBags()->push_back(c);

			}

			pObjectLayer->getGameObjects()->push_back(pGameObject);
		}
	}

	pLayers->push_back(pObjectLayer);
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers, std::vector<TileLayer*> *pGrassLayers)
{
	TileLayer* pTileLayer = new TileLayer(m_tileSize, m_width, m_height, *pTilesets);

	bool collidable = false;
	bool grass = false;

	// tile data
	std::vector<std::vector<int>> data;

	std::string decodedIDs;
	TiXmlElement* pDataNode = nullptr;

	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("properties"))
		{
			for (TiXmlElement* property = e->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
			{
				if (property->Value() == std::string("property"))
				{
					if (property->Attribute("name") == std::string("collidable"))
					{
						collidable = true;
					}

					else if (property->Attribute("name") == std::string("BigGrass"))
					{
						grass = true;
					}
				}
			}
		}

		if (e->Value() == std::string("data"))
		{
			pDataNode = e;
		}
	}

	for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
	{
		TiXmlText* text = e->ToText();
		std::string t = text->Value();
		decodedIDs = base64_decode(t);
	}

	// uncompress zlib compression
	uLongf sizeofids = m_width * m_height * sizeof(int);
	std::vector<int> ids(m_width * m_height);
	uncompress((Bytef*)&ids[0], &sizeofids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

	std::vector<int> layerRow(m_width);

	for (int j = 0; j < m_height; j++)
	{
		data.push_back(layerRow);
	}

	for (int rows = 0; rows < m_height; rows++)
	{
		for (int cols = 0; cols < m_width; cols++)
		{
			data[rows][cols] = ids[rows * m_width + cols];
		}
	}

	pTileLayer->setTileIDs(data);
	pTileLayer->setMapWidth(m_width);

	if (collidable)
	{
		pCollisionLayers->push_back(pTileLayer);
	}

	else if (grass)
	{
		pGrassLayers->push_back(pTileLayer);
		
	}

	pLayers->push_back(pTileLayer);
}