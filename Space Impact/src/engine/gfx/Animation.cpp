#include "Animation.h"

#include "../Application.h"

Animation::Animation(const std::shared_ptr<Sprite>& spr, int numberOfSprites, float spriteWidth, float spriteHeight) : m_SpriteWidth(spriteWidth / numberOfSprites), m_SpriteHeight(spriteHeight),
	m_NoOfSprites(numberOfSprites), m_SpriteSheet(spr){ }

void Animation::Play(const vec2& position, const vec2& size, float speed)
{
	if (m_LastPlayed > speed)
	{
		m_CurrentSprite++;
		m_LastPlayed = 0;
	}

	if (m_CurrentSprite >= m_NoOfSprites)
		m_CurrentSprite = 0;

	m_LastPlayed += Time::deltaTime;

	D2D_RECT_F src = D2D1::RectF(
		(float)((m_CurrentSprite % m_NoOfSprites) * m_SpriteWidth),
		(float)((m_CurrentSprite / m_NoOfSprites) * m_SpriteHeight),
		(float)((m_CurrentSprite % m_NoOfSprites) * m_SpriteWidth) + m_SpriteWidth,
		(float)((m_CurrentSprite / m_NoOfSprites) * m_SpriteHeight) + m_SpriteHeight
	);

	D2D_RECT_F dest = D2D1::RectF(
		position.x,
		position.y,
		position.x + size.x,
		position.y + size.y
	);

	m_SpriteSheet->Draw(src, dest);
}
