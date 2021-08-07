#include "FirstBoss.h"

#include "../GameManager.h"
#include "Bullet.h"
#include "../engine/utils/Random.h"
#include "../engine/Win32Window.h"
#include "../engine/utils/SpriteManager.h"

FirstBoss::FirstBoss(const wchar_t* filepath, const vec2& pos, const vec2& size) : ShootingEnemy(SpriteManager::loadSprite(filepath), pos, size)
{ 
	m_Health = 50;
	Animation anim(m_Sprite, 2, 200.5f, 91);
	m_Animation = anim;
	m_ShotCooldown = 1.0f;
}

void FirstBoss::onUpdate(float deltaTime)
{
	if (m_Health > 0)
	{
		if (m_Position.x < 0 - m_Size.x)
			DestroyEntity(this);

		m_GunPosition.x = m_Position.x;
		m_GunPosition.y = m_Position.y + m_Size.y / 2.0f - m_BulletSize.y / 2;

		if (m_Position.y < 75.0f && m_Direction == -1)
			m_Direction = 1;

		if (m_Position.y > Window::Get()->getHeight() - m_Size.y && m_Direction == 1)
			m_Direction = -1;

		m_Position.y += m_Speed * deltaTime * m_Direction;

		if (m_Position.x > Window::Get()->getWidth() - 400.0f)
			m_Position.x -= m_Speed * deltaTime;

		if (m_CurrentShotTime > m_ShotCooldown)
		{
			Bullet* bullet = CreateEntity<Bullet>(m_BulletSprite, m_GunPosition, m_BulletSize);
			bullet->getSpeed() = -500.0f;
			GameManager::pushBackEnemyBullet(bullet);
			m_CurrentShotTime = 0.0f;
		}

		m_CurrentShotTime += deltaTime;

		m_Animation.Play(m_Position, m_Size, 0.2f);
	}
	else 
	{
		m_Size = { 75.0f, 75.0f };
		m_DeathAnimation.Play(m_Position, m_Size, 0.12f);
	}

	if (m_Health <= 0)
		DestroyEntity(this, 0.2f);
}
