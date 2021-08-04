#pragma once
#include "../engine/entity/Entity.h"
#include <vector>

class Player : public Entity
{
public:
	Player(const wchar_t* filepath, const vec2& pos = { 0, 0 }, const vec2& size = { 1, 1 });
	~Player() = default;

	virtual void onCreate() override;
	virtual void onUpdate(float deltaTime) override;

	void takeDamage(int dmg) { m_Health -= dmg; }
	void addScore(int points) { m_Score += points; }
	const int getScore() const { return m_Score; }

private:
	float m_Speed = 450.0f;

	std::shared_ptr<Sprite> m_HeartSprite;
	vec2 m_HeartSize = { 50.0f, 50.0f };
	float m_HeartOffset = 10.0f;
	float m_HeartYPosition = 10.0f;

	std::shared_ptr<Sprite> m_BulletSprite;
	vec2 m_BulletSize = { 40.0f, 15.0f };

	bool m_wasSpacePressed = false;
	bool m_isSpacePressed = false;

	vec2 m_GunPosition;

	int m_Health = 3;

	int m_Score = 0;
};