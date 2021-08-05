#pragma once
#include "../utils/Maths.h"
#include "Sprite.h"

#include "../utils/Maths.h"

#include <memory>

class Animation
{
public:
	Animation(const std::shared_ptr<Sprite>& spr, int numberOfSprites, float spriteWidth, float spriteHeight);
	Animation() = default;
	~Animation() = default;

	void Play(const vec2& position, const vec2& size, float speed);

private:
	std::shared_ptr<Sprite> m_SpriteSheet;

	float m_SpriteWidth;
	float m_SpriteHeight;
	int m_NoOfSprites;

	int m_CurrentSprite = 0;

	float m_LastPlayed = 0.0f;
};