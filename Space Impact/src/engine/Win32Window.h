#pragma once
#include <Windows.h>
#include "utils/Types.h"

class Window
{
public:
	Window(const wchar_t* name, uint16 width, uint16 height, unsigned long flags = WS_OVERLAPPEDWINDOW);

	void pollEvents();

	uint16 getWidth() { return m_Width; }
	uint16 getHeight() { return m_Height; }

	HWND& getHandle() { return m_WindowHandle; }

	void setWidth(uint16 width) { m_Width = width; }
	void setHeight(uint16 height) { m_Height = height; }

	bool& isRunning() { return m_isRunning; }

	static Window* Get() { return m_Instance; }

private:
	HWND m_WindowHandle;
	WNDCLASS m_WindowClass;

	uint16 m_Width;
	uint16 m_Height;
	wchar_t* m_Name;
	bool m_isRunning;

	static Window* m_Instance;
};