#include "Bullet.h"

Bullet::Bullet(const std::shared_ptr<Sprite>& sprite, const vec2& pos, const vec2& size) : Entity(sprite, pos, size)
{

}

void Bullet::onCreate()
{
}

void Bullet::onUpdate(float deltaTime)
{
	m_Position.x += m_Speed * deltaTime;

	if (m_Position.x > 1600.0f)
	{
   		m_isAlive = false;
	}
}
