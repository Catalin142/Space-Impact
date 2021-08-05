#include "Background.h"

Background::Background(const std::shared_ptr<Sprite>& sprite, const vec2& pos, const vec2& size) : Entity(sprite, pos, size)
{ 
	m_InitialPosition = pos.x;
}

void Background::onCreate()
{  }

void Background::onUpdate(float deltaTime)
{
	m_Position.x -= m_Speed * deltaTime;

	if (m_Position.x < m_InitialPosition - m_Size.x)
	{
		m_Position.x = m_InitialPosition - m_Speed * deltaTime;
	}
}
