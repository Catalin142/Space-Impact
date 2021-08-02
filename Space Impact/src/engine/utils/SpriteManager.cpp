#pragma once
#include "SpriteManager.h"

#include "../utils/Macros.h"
#include "../utils/BMPLoader.h"

std::vector<std::shared_ptr<Sprite>> SpriteManager::m_Sprites;

std::shared_ptr<Sprite> SpriteManager::loadSprite(const wchar_t* filepath)
{
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(filepath);
	m_Sprites.push_back(sprite);
	return sprite;
}

void SpriteManager::clearResources()
{
	for (const auto& sprite : m_Sprites)
		sprite->Destroy();
}
