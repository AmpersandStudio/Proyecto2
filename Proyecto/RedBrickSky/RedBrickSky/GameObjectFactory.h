#pragma once

#include "GameObject.h"

#include <string>
#include <map>

#include "checkML.h"

class BaseCreator
{
public:
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator() {}
};

class GameObjectFactory
{
public:
	static GameObjectFactory* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new GameObjectFactory();
		}
		return s_pInstance;
	}

	bool registerType(std::string typeID, BaseCreator* pCreator)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
		
		if (it != m_creators.end())
		{
			delete pCreator;
			return false;
		}

		m_creators[typeID] = pCreator;
		return true;
	}

	GameObject* create(std::string typeID)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

		if (it == m_creators.end())
		{
			std::cout << "Could not find type: " << typeID << "\n";
			return NULL;
		}

		BaseCreator* pCreator = (*it).second;
		return pCreator->createGameObject();
	}

	~GameObjectFactory() {
		std::map<std::string, BaseCreator*>::iterator it = m_creators.begin();
		for (it; it != m_creators.end(); it++) {
			if ((*it).second != nullptr)
				delete ((*it).second);
		}
	}

private:
	GameObjectFactory() {}

	static GameObjectFactory* s_pInstance;

	std::map<std::string, BaseCreator*> m_creators;
};

typedef GameObjectFactory TheGameObjectFactory;
