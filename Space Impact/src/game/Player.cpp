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
	if (GetAsyncKeyState(VK_W) && m_Position.y > 75.0f)
		m_Position.y -= m_Speed * deltaTime;
	
	if (GetAsyncKeyState(VK_S) && m_Position.y < Window::Get()->getHeight() - m_Size.y)
		m_Position.y += m_Speed * deltaTime;
	
	m_GunPosition.x = m_Position.x + m_Size.x - 20.0f;
	m_GunPosition.y = m_Position.y + m_Size.y / 2.0f - m_BulletSize.y / 2;

	m_wasSpacePressed = m_isSpacePressed;
	m_isSpacePressed = GetAsyncKeyState(VK_SPACE);

	if (m_wasSpacePressed != m_isSpacePressed && m_wasSpacePressed == false)
	{
		Bullet* bullet = CreateEntity<Bullet>(m_BulletSprite, m_GunPosition, m_BulletSize);
		GameManager::pushBackPlayerBullet(bullet);
	}

	for (int i = 0; i < m_Health; i++)
	{
		vec2 heartPosition = { i * (m_HeartSize.x + 5.0f) + m_HeartOffset, m_HeartYPosition };
		m_HeartSprite->Draw(heartPosition, m_HeartSize);
	}

	if (m_Health == 0)
		DestroyEntity(this);
}
