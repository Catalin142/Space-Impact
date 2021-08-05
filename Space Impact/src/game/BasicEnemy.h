#pragma once
#include "../engine/entity/Entity.h"
#include "../engine/gfx/Animation.h"

class BasicEnemy : public Entity
{
public:
	BasicEnemy(const std::shared_ptr<Sprite>& sprite, const vec2& pos = { 0, 0 }, const vec2& size = { 1, 1 });
	~BasicEnemy() = default;

	virtual void onCreate() override;
	virtual void onUpdate(float deltaTime) override;

	void setDeathAnimation(Animation& anim);

	void takeDamage(int dmg) { m_Health -= dmg; }
	bool isAlive() { return m_Health; }

private:
	float m_Speed = 250.0f;
	vec2 m_TargetLocation = { 0.0f, 0.0f };

	Animation m_Animation;
	Animation m_DeathAnimation;

	int m_Health = 2;
};