#include "Bullet.h"

#include "../engine/Win32Window.h"

Bullet::Bullet(const std::shared_ptr<Sprite>& sprite, const vec2& pos, const vec2& size) : Entity(sprite, pos, size) { }

void Bullet::onCreate() 
{
	m_Explode = false;
}

void Bullet::onUpdate(float deltaTime)
{
	m_Position.x += m_Speed * deltaTime;

	if (m_Speed > 0)
	{
		if (m_Position.x > Window::Get()->getWidth() - m_Size.x)
		{
			DestroyEntity(this);
		}
	}
	else
	{
		if (m_Position.x < 0)
		{
			DestroyEntity(this);
		}
	}
}
