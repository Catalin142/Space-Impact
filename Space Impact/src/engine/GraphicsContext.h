#pragma once

#include "utils/Types.h"
#include "Win32Window.h"

#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include <memory>

class GraphicsContext
{
public:
	GraphicsContext(std::shared_ptr<Window>& window);
	~GraphicsContext();

	void Destory() { this->~GraphicsContext(); }

	ID2D1HwndRenderTarget* getRenderTarget() { return m_RenderTarget; }

	void onResize(uint16 width, uint16 height);

	void beginDraw(); // tot ce randez tre sa fie intre astia doi
	void endDraw();

	void clearScreen(float r = 0.0f, float g = 0.0f, float b = 0.0f);

	static GraphicsContext* Get() { return m_Instance; }

private:
	ID2D1Factory* m_Factory = NULL;
	ID2D1HwndRenderTarget* m_RenderTarget = NULL;
	PAINTSTRUCT m_PaintStruct;

	std::shared_ptr<Window> m_Window;

	static GraphicsContext* m_Instance;
};