#pragma once
#include "../engine/entity/Entity.h"
#include "../engine/gfx/Sprite.h"

class Bullet : public Entity
{
public:
	Bullet(const std::shared_ptr<Sprite>& sprite, const vec2& pos = { 0, 0 }, const vec2& size = { 1, 1 });

	virtual void onCreate() override;
	virtual void onUpdate(float deltaTime) override;

	float& getSpeed() { return m_Speed; }

private:
	float m_Speed = 1000.0f;
};