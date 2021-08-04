#include "BasicEnemy.h"

#include "../engine/utils/Random.h"
#include "../engine/Win32Window.h"
#include "../GameManager.h"

BasicEnemy::BasicEnemy(const std::shared_ptr<Sprite>& sprite, const vec2& pos, const vec2& size) : Entity(sprite, pos, size), 
m_Animation(sprite, 2, 91.8f, 23.0f) { }

void BasicEnemy::onCreate()
{
	m_TargetLocation.x = m_Position.x;
	m_TargetLocation.y = m_Position.y;
	m_Tag = "BasicEnemy";
	m_HasAnimation = true;
	GameManager::pushBackEnemy(this);
}

void BasicEnemy::onUpdate(float deltaTime)
{
	if (m_Position.x < 0 - m_Size.x)
		DestroyEntity(this);

	if (m_TargetLocation.x == m_Position.x && m_TargetLocation.y == m_Position.y)
	{
		m_TargetLocation.x = Random::Float() * m_Position.x - 200.0f;
		m_TargetLocation.y = 100.0f + Random::Float() * (Window::Get()->getHeight() - 200.0f);
	}

	m_Animation.Play(m_Position, m_Size, 0.4f);

	m_Position = moveTowards(m_Position, m_TargetLocation, deltaTime * m_Speed);

	if (m_Health <= 0)
		DestroyEntity(this);
}
