#include "Player.h"

#include "../GameManager.h"
#include "Bullet.h"
#include "../engine/utils/Macros.h"
#include "../engine/utils/SpriteManager.h"
#include "../engine/Win32Window.h"

Player::Player(const wchar_t* filepath, const vec2& pos, const vec2& size) : Entity(filepath, pos, size) { }

void Player::onCreate()
{
	m_BulletSprite = SpriteManager::loadSprite(L"res/Bullet.png");
	m_HeartSprite = SpriteManager::loadSprite(L"res/Heart.png");

	m_Tag = "Player";
	GameManager::setPlayer(this);
}

void Player::onUpdate(float deltaTime)
{
	if (m_Health > 0)
	{
		if (GetAsyncKeyState(VK_W) && m_Position.y > 75.0f)
			m_Position.y -= m_Speed * deltaTime;

		if (GetAsyncKeyState(VK_S) && m_Position.y < Window::Get()->getHeight() - m_Size.y)
			m_Position.y += m_Speed * deltaTime;

		m_GunPosition.x = m_Position.x + m_Size.x - 20.0f;
		m_GunPosition.y = m_Position.y + m_Size.y / 2.0f - m_BulletSize.y / 2;

		m_wasSpacePressed = m_isSpacePressed;
		m_isSpacePressed = GetAsyncKeyState(VK_SPACE);

		if (m_wasSpacePressed != m_isSpacePressed && m_wasSpacePressed == false && m_GunLast > m_GunCooldown)
		{
			Bullet* bullet = CreateEntity<Bullet>(m_BulletSprite, m_GunPosition, m_BulletSize);
			bullet->getSpeed() = 350.0f;
			GameManager::pushBackPlayerBullet(bullet);

			m_GunLast = 0.0f;
		}

		m_GunLast += deltaTime;

		for (int i = 0; i < m_Health; i++)
		{
			vec2 heartPosition = { i * (m_HeartSize.x + 5.0f) + m_HeartOffset, m_HeartYPosition };
			m_HeartSprite->Draw(heartPosition, m_HeartSize);
		}
	}
	else
	{
		m_HasAnimation = true;
		m_Size = { 100.0f, 100.0f };
		m_DeathAnimation.Play(m_Position, m_Size, 0.12f);
	}

	if (m_Health <= 0)
		DestroyEntity(this, 0.2f);
}

void Player::setDeathAnimation(Animation& anim)
{
	m_DeathAnimation = anim;
}
