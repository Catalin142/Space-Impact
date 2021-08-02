#pragma once
#include <wincodec.h>

#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "../utils/Maths.h"
#include <memory>

class Sprite
{
public:
	Sprite(const wchar_t* filepath);
	Sprite(const std::shared_ptr<Sprite>& other);
	~Sprite();

	void Draw(const vec2& position, const vec2& size);
	void Destroy();

private:
	ID2D1Bitmap* m_Bitmap;
	wchar_t* m_Filepath;

	vec2 m_Position = { 0.0f, 0.0f };
	vec2 m_Scale = { 1.0f, 1.0f };

	float m_Opacity = 1.0f;
};