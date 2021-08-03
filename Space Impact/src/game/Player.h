#pragma once
#include "../engine/entity/Entity.h"
#include "../engine/gfx/Sprite.h"

#include "Bullet.h"

#include <vector>

class Player : public Entity
{
public:
	Player(const wchar_t* filepath, const vec2& pos = { 0, 0 }, const vec2& size = { 1, 1 });
	~Player() = default;

	virtual void onCreate() override;
	virtual void onUpdate(float deltaTime) override;

	void takeDamage(int dmg) { m_Health -= dmg; }

private:
	float m_Speed = 450.0f;
	std::vector<Bullet*> m_Bullets;

	std::shared_ptr<Sprite> m_BulletSprite;
	vec2 m_BulletSize = { 40.0f, 15.0f };

	bool m_wasSpacePressed = false;
	bool m_isSpacePressed = false;

	vec2 m_GunPosition;

	int m_Health = 3;
};