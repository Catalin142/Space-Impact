#include "Player.h"

#include "../engine/utils/Macros.h"
#include "../engine/utils/SpriteManager.h"

Player::Player(const wchar_t* filepath, const vec2& pos, const vec2& size) : Entity(filepath, pos, size) { }

void Player::onCreate()
{
	m_BulletSprite = SpriteManager::loadSprite(L"res/PlayerBullet.png");
}

void Player::onUpdate(float deltaTime)
{
	m_LastGun += deltaTime;

	if (GetAsyncKeyState(VK_W))
		m_Position.y -= m_Speed * deltaTime;
	
	if (GetAsyncKeyState(VK_S))
		m_Position.y += m_Speed * deltaTime;

	m_GunPosition.x = m_Position.x + m_Size.x - 20.0f;
	m_GunPosition.y = m_Position.y + m_Size.y / 2.0f - m_BulletSize.y / 2;

	if (GetAsyncKeyState(VK_SPACE) && m_LastGun > m_GunCooldown)
	{
		Bullet* bullet = CreateEntity<Bullet>(m_BulletSprite, m_GunPosition, m_BulletSize);
		m_LastGun = 0.0f;
	}

}
