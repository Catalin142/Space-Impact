#include "TextRenderer.h"

#include "../GraphicsContext.h"
#include "../utils/Macros.h"

#include <cassert>
#include <algorithm>
#include <iterator>

IDWriteFactory5* TextFormatManager::m_Factory = nullptr;
std::unordered_map<std::string, Font> TextFormatManager::m_TextFormats;

void TextFormatManager::createFormat(const std::string& name, const wchar_t* font, float size)
{
	HRESULT hr;
	if (m_Factory == nullptr)
	{
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_Factory));
	}
	
	if (m_TextFormats.find(name) == m_TextFormats.end())
	{
		IDWriteTextFormat* format;
		Font newFont;
		m_Factory->CreateTextFormat(
			font,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			size,
			L"en-us",
			&format
		);

		format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		newFont.m_Format = format;
		newFont.m_Size = size;

		m_TextFormats[name] = newFont;
	}
}

Font TextFormatManager::getFormat(const std::string& name)
{
	if (m_TextFormats.find(name) != m_TextFormats.end())
		return m_TextFormats[name];
}

void TextFormatManager::clearResources()
{
	for (auto& formats : m_TextFormats)
		SAFE_RELEASE(formats.second.m_Format);
}

void TextRenderer::RenderString(const wchar_t* text, const vec2& position, Font format, ID2D1SolidColorBrush* brush)
{
	UINT32 length = (UINT32)wcslen(text);

	D2D1_RECT_F pos = D2D1::RectF(
		position.x, position.y,
		position.x + (60.0f * length), position.y + 60.0f
	);

	GraphicsContext::Get()->getRenderTarget()->DrawText(
		text,
		length,
		format.m_Format, 
		pos,
		brush
	);
}

void TextRenderer::CenterString(const wchar_t* text, Font format, float offset, ID2D1SolidColorBrush* brush)
{
	UINT32 length = (UINT32)wcslen(text);

	D2D1_RECT_F pos = D2D1::RectF(
		0.0f, 0.0f,
		Window::Get()->getWidth(), offset
	);

	GraphicsContext::Get()->getRenderTarget()->DrawText(
		text,
		length,
		format.m_Format,
		pos,
		brush
	);
}

void TextRenderer::RenderNumbersFromPNG(std::shared_ptr<Sprite>& atlas, const std::string& number, vec2 pos, vec2 size)
{
	auto it = number.begin();

	for(int i = 0; i < number.size(); i++)
	{
		int digit = number[i] - '0';

		D2D_RECT_F src = D2D1::RectF(
			(float)((digit % 10) * (atlas->getBitmapSize().x / 10.0f)),
			(float)((digit / 10) * atlas->getBitmapSize().y),
			(float)((digit % 10) * (atlas->getBitmapSize().x / 10.0f)) + (atlas->getBitmapSize().x / 10.0f),
			(float)((digit / 10) * atlas->getBitmapSize().y) + atlas->getBitmapSize().y
		);

		D2D_RECT_F dest = D2D1::RectF(
			pos.x,
			pos.y,
			pos.x + size.x,
			pos.y + size.y
		);

		pos.x += size.x;

		atlas->Draw(src, dest);
	}
}

#define MAX_LET 26

void TextRenderer::RenderTextFromPNG(std::shared_ptr<Sprite>& atlas, const std::string& string, vec2 pos, vec2 size)
{
	std::string text;
	std::transform(string.begin(), string.end(), std::back_inserter(text), ::toupper);
	auto it = string.begin();

	for (int i = 0; i < text.size(); i++)
	{
		int digit = text[i] - 'A';

		D2D_RECT_F src = D2D1::RectF(
			(float)((digit % MAX_LET) * (atlas->getBitmapSize().x / MAX_LET)),
			(float)((digit / MAX_LET) * atlas->getBitmapSize().y),
			(float)((digit % MAX_LET) * (atlas->getBitmapSize().x / MAX_LET)) + (atlas->getBitmapSize().x / MAX_LET),
			(float)((digit / MAX_LET) * atlas->getBitmapSize().y) + atlas->getBitmapSize().y
		);

		D2D_RECT_F dest = D2D1::RectF(
			pos.x,
			pos.y,
			pos.x + size.x,
			pos.y + size.y
		);

		pos.x += size.x;

		atlas->Draw(src, dest);
	}
}
