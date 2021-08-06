#include "EntityManager.h"

#include <algorithm>

std::vector<Entity*> EntityManager::m_Entities;

void EntityManager::addEntity(Entity* entity)
{
	auto it = std::find(m_Entities.begin(), m_Entities.end(), entity);
	if (it == m_Entities.end())
		m_Entities.push_back(entity);
}

void EntityManager::removeEntity(Entity* entity)
{
	auto it = std::find(m_Entities.begin(), m_Entities.end(), entity);
	if (it != m_Entities.end())
		m_Entities.erase(it);
}

void EntityManager::updateEntities(float deltaTime)
{
	for (int i = 0; i < m_Entities.size(); i++)
	{
		if (m_Entities[i])
		{
			if (m_Entities[i]->Initialized == false)
			{
				m_Entities[i]->Initialized = true;
				m_Entities[i]->onCreate();
			}

			m_Entities[i]->onUpdate(deltaTime);

			if (m_Entities[i]->m_HasAnimation == false)
				m_Entities[i]->onDraw();
		}
	}
}

void EntityManager::clearResources()
{
	std::for_each(m_Entities.begin(), m_Entities.end(), [](Entity* ent) -> void {
		ent->getStatus() = false; });
	checkForDeadEntities();
}

void EntityManager::checkForDeadEntities()
{
	for (auto p = m_Entities.begin(); p != m_Entities.end();)
	{
		if ((*p)->getStatus() == false)
		{
			delete* p;
			*p = nullptr;
			p = m_Entities.erase(p);
		}
		else p++;
	}
}
