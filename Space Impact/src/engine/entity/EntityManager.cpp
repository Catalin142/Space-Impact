#include "EntityManager.h"

std::vector<Entity*> EntityManager::m_Entities;

void EntityManager::addEntity(Entity* entity)
{
	auto it = std::find(m_Entities.begin(), m_Entities.end(), entity);
	if (it == m_Entities.end())
	{
		m_Entities.push_back(entity);
	}
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
			m_Entities[i]->onUpdate(deltaTime);
			m_Entities[i]->onDraw();
		}
	}

	checkForDeadEntities();
}

void EntityManager::clearResources()
{
	for (auto& ent : m_Entities)
		ent->getStatus() = true;

	checkForDeadEntities();
}

void EntityManager::checkForDeadEntities()
{
	m_Entities.erase(std::remove_if(m_Entities.begin(), m_Entities.end(), [](Entity* ent) { return !ent->getStatus(); }), m_Entities.end());
}
