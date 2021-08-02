#include "Entity.h"
#include "../utils/SpriteManager.h"
#include "EntityManager.h"

Entity::Entity(const wchar_t* filepath, const vec2& pos, const vec2& size) : m_Position(pos), m_Size(size)
{
	m_Sprite = SpriteManager::loadSprite(filepath);
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
