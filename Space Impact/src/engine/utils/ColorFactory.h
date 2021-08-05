#pragma once

#include <unordered_map>

#include <d2d1.h>
#pragma comment(lib, "d2d1")

class ColorFactory
{
public:
	static void createColor(const std::string& name, float r, float g, float b);
	static ID2D1SolidColorBrush* getColor(const std::string& name);

	static void clearResources();

private:
	static std::unordered_map<std::string, ID2D1SolidColorBrush*> m_Colors;

private:
	ColorFactory() = default;
	~ColorFactory() = default;
};
