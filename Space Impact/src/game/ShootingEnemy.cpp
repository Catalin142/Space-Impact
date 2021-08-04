#include "ShootingEnemy.h"

#include "../GameManager.h"
#include "Bullet.h"
#include "../engine/utils/Random.h"
#include "../engine/Win32Window.h"
#include "../engine/utils/SpriteManager.h"

ShootingEnemy::ShootingEnemy(const std::shared_ptr<Sprite>& sprite, const vec2& pos, const vec2& size) : Entity(sprite, pos, size), 
m_Animation(sprite, 2, 60.4f, 35.f) { }

void ShootingEnemy::onCreate()
{
	m_TargetLocation.x = m_Position.x;
	m_TargetLocation.y = m_Position.y;
	m_BulletSprite = SpriteManager::loadSprite(L"res/Bullet.png");
	m_Tag = "ShootingEnemy";
	m_HasAnimation = true;
	GameManager::pushBackEnemy(this);
}

void ShootingEnemy::onUpdate(float deltaTime)
{
	if (m_Position.x < 0 - m_Size.x)
		DestroyEntity(this);

	if (m_TargetLocation.x == m_Position.x && m_TargetLocation.y == m_Position.y)
	{
		m_TargetLocation.x = Random::Float() * m_Position.x - 200.0f;
		m_TargetLocation.y = 100.0f + Random::Float() * (Window::Get()->getHeight() - 200.0f);
	}

	m_GunPosition.x = m_Position.x;
	m_GunPosition.y = m_Position.y + m_Size.y / 2.0f - m_BulletSize.y / 2;

	if (m_CurrentShotTime > m_ShotCooldown)
	{
		Bullet* bullet = CreateEntity<Bullet>(m_BulletSprite, m_GunPosition, m_BulletSize);
		bullet->getSpeed() = -bullet->getSpeed() * 0.7f;
		GameManager::pushBackEnemyBullet(bullet);
		m_CurrentShotTime = 0.0f;
	}

	m_CurrentShotTime += deltaTime;

	m_Animation.Play(m_Position, m_Size, 1.0f);

	m_Position = moveTowards(m_Position, m_TargetLocation, deltaTime * m_Speed);

	if (m_Health <= 0)
		DestroyEntity(this);
}