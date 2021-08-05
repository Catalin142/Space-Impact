#pragma once
#include "../engine/entity/Entity.h"
#include "../engine/gfx/Sprite.h"

class Background : public Entity
{
public:
	Background(const std::shared_ptr<Sprite>& sprite, const vec2& pos = { 0, 0 }, const vec2& size = { 1, 1 });

	virtual void onCreate() override;
	virtual void onUpdate(float deltaTime) override;

private:
	float m_Speed = 300.0f;
	float m_InitialPosition;
};