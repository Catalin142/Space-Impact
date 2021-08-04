#pragma once
#include "Sprite.h"
#include "../GraphicsContext.h"
#include "../utils/BMPLoader.h"
#include "../utils/Macros.h"

Sprite::Sprite(const wchar_t* filepath) : m_Bitmap(nullptr), m_Filepath(const_cast<wchar_t*>(filepath))
{
	m_Bitmap = BMPLoader::Load(filepath);
}

Sprite::Sprite(const std::shared_ptr<Sprite>& other)
{
	m_Bitmap = other->m_Bitmap;
	m_Filepath = other->m_Filepath;
	m_Opacity = other->m_Opacity;
}

Sprite::~Sprite()
{
	Destroy();
}

void Sprite::Draw(const vec2& position, const vec2& size)
{
	if (m_Bitmap != nullptr)
	{
		GraphicsContext::Get()->getRenderTarget()->DrawBitmap(m_Bitmap, D2D1::RectF(position.x, position.y, position.x + size.x, position.y + size.y), m_Opacity,
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
			D2D1::RectF(0.0f, 0.0f, m_Bitmap->GetSize().width, m_Bitmap->GetSize().height));
	}
}

void Sprite::Draw(const D2D_RECT_F& src, const D2D_RECT_F& dest)
{
	if (m_Bitmap != nullptr)
	{
		GraphicsContext::Get()->getRenderTarget()->DrawBitmap(m_Bitmap, dest, m_Opacity,
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, src);

	}
}

void Sprite::Destroy()
{
	SAFE_RELEASE(m_Bitmap);
}
