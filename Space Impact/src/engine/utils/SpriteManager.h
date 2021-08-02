#pragma once
#include <vector>
#include <memory>

#include "../gfx/Sprite.h"

class SpriteManager
{
public:
	static std::shared_ptr<Sprite> loadSprite(const wchar_t* filepath);
	static void clearResources();

private:
	static std::vector<std::shared_ptr<Sprite>> m_Sprites;

private:
	SpriteManager() = default;
	~SpriteManager() = default;
};