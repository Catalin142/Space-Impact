#pragma once

#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include <dwrite.h>
#pragma comment(lib, "Dwrite")

#include <string>
#include <unordered_map>

#include "../utils/Maths.h"
#include "../utils/Types.h"

struct Font
{
	IDWriteTextFormat* m_Format;
	uint32 m_Size;
};

class TextFormatManager
{
public:
	static void createFormat(const std::string& name, const wchar_t* font, float size);
	static Font getFormat(const std::string& name);

	static void clearResources();

private:
	static IDWriteFactory* m_Factory;
	static IDWriteFontCollection* m_Collection;
	static std::unordered_map<std::string, Font> m_TextFormats;

private:
	TextFormatManager() = default;
	~TextFormatManager() = default;
};


class TextRenderer
{
public:
	static void RenderString(const wchar_t* text, const vec2& position, Font format, ID2D1SolidColorBrush* brush);

private:
	TextRenderer() = default;
	~TextRenderer() = default;
};