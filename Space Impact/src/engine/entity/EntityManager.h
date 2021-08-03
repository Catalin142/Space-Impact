#pragma once

#include "Entity.h"

#include <vector>
#include <memory>

class EntityManager
{
public:
	static void addEntity(Entity* entity);
	static void removeEntity(Entity* entity);

	static void updateEntities(float deltaTime);

	static void clearResources();
	static void checkForDeadEntities();

private:
	static std::vector<Entity*> m_Entities;

private:
	EntityManager() = default;
	~EntityManager() = default;

};