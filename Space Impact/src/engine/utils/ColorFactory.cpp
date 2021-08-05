#include "ColorFactory.h"

#include "../GraphicsContext.h"
#include "Macros.h"

std::unordered_map<std::string, ID2D1SolidColorBrush*> ColorFactory::m_Colors;

void ColorFactory::createColor(const std::string& name, float r, float g, float b)
{
	if (m_Colors.find(name) == m_Colors.end())
	{
		ID2D1SolidColorBrush* color;
		GraphicsContext::Get()->getRenderTarget()->CreateSolidColorBrush(
			D2D1::ColorF(r, g, b),
			&color
		);

		m_Colors[name] = color;
	}
}

ID2D1SolidColorBrush* ColorFactory::getColor(const std::string& name)
{
	if (m_Colors.find(name) != m_Colors.end())
		return m_Colors[name];
}

void ColorFactory::clearResources()
{
	for (auto& color : m_Colors)
		SAFE_RELEASE(color.second);
}
