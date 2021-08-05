#pragma once
#include "../engine/entity/Entity.h"
#include "../engine/gfx/Animation.h"

class ShootingEnemy : public Entity
{
public:
	ShootingEnemy(const std::shared_ptr<Sprite>& sprite, const vec2& pos = { 0, 0 }, const vec2& size = { 1, 1 });
	virtual ~ShootingEnemy() = default;

	virtual void onCreate() override;
	virtual void onUpdate(float deltaTime) override;

	void setDeathAnimation(Animation& anim);

	void takeDamage(int dmg) { m_Health -= dmg; }
	bool isAlive() { return m_Health; }

protected:
	float m_Speed = 200.0f;
	vec2 m_TargetLocation = { 0.0f, 0.0f };

	Animation m_Animation;
	Animation m_DeathAnimation;

	std::shared_ptr<Sprite> m_BulletSprite;
	vec2 m_BulletSize = { 45.0f, 20.0f };

	float m_ShotCooldown = 2.0f;
	float m_CurrentShotTime = m_ShotCooldown;

	vec2 m_GunPosition;

	int m_Health = 3;
};