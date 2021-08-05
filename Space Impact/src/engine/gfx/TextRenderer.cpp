#include "TextRenderer.h"

#include "../GraphicsContext.h"
#include "../utils/Macros.h"

#include <cassert>

IDWriteFactory* TextFormatManager::m_Factory = nullptr;
IDWriteFontCollection* TextFormatManager::m_Collection = nullptr;
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

		format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
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
	DWRITE_TEXT_METRICS textMetrics;

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
