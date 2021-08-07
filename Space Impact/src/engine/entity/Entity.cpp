#include "Entity.h"
#include "../utils/SpriteManager.h"
#include "EntityManager.h"

#include "../Application.h"

Entity::Entity(const wchar_t* filepath, const vec2& pos, const vec2& size) : m_Position(pos), m_Size(size)
{
	m_Sprite = SpriteManager::loadSprite(filepath);
	m_CollisionBox.m_Min = { m_Position.x, m_Position.y };
	m_CollisionBox.m_Max = { m_Position.x + m_Size.x, m_Position.y + m_Size.y};
	EntityManager::addEntity(this);
}

Entity::Entity(const std::shared_ptr<Sprite>& sprite, const vec2& pos, const vec2& size) : m_Position(pos), m_Size(size), m_Sprite(sprite)
{
	EntityManager::addEntity(this);
}

void Entity::onDraw()
{
	m_Sprite->Draw(m_Position, m_Size);
}

void DestroyEntity(Entity* entity, float ts)
{
	if (entity->m_Timer >= ts)
		entity->m_isAlive = false;
	else entity->m_Timer += Time::deltaTime;
}

bool checkCollision(Entity* left, Entity* right)
{
	left->m_CollisionBox.m_Min = { left->m_Position.x, left->m_Position.y };
	left->m_CollisionBox.m_Max = { left->m_Position.x + left->m_Size.x, left->m_Position.y + left->m_Size.y };

	right->m_CollisionBox.m_Min = { right->m_Position.x, right->m_Position.y };
	right->m_CollisionBox.m_Max = { right->m_Position.x + right->m_Size.x, right->m_Position.y + right->m_Size.y };

	return (left->m_CollisionBox.m_Max > right->m_CollisionBox.m_Min
		&& left->m_CollisionBox.m_Min < right->m_CollisionBox.m_Max) || 
		(left->m_CollisionBox.m_Max < right->m_CollisionBox.m_Min && 
			left->m_CollisionBox.m_Min > right->m_CollisionBox.m_Max);
}
