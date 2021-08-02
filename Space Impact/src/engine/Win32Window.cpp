#include "Win32Window.h"

#include <iostream>
#include <windef.h>
#include <cassert>

#include "GraphicsContext.h"
#include "utils/SpriteManager.h"
#include "entity/EntityManager.h"

Window* Window::m_Instance = nullptr;

static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
	{
		auto window = Window::Get();
		window->setWidth(LOWORD(lParam));
		window->setHeight(HIWORD(lParam));

		if (GraphicsContext::Get() != nullptr)
			GraphicsContext::Get()->onResize(window->getWidth(), window->getHeight());
	} break;

	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
	} break;

	case WM_DESTROY:
	{
		EntityManager::clearResources();
		SpriteManager::clearResources();
		PostQuitMessage(0);
	} break;

	default: return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

Window::Window(const wchar_t* name, uint16 width, uint16 height, unsigned long flags) : m_Name(const_cast<wchar_t*>(name)), m_Width(width), m_Height(height), m_isRunning(true)
{
	m_Instance = this;
	
	m_WindowClass = { };

	HINSTANCE hInstance = GetModuleHandle(NULL);

	m_WindowClass.lpfnWndProc = WindowProcedure;
	m_WindowClass.hInstance = GetModuleHandle(NULL);
	m_WindowClass.lpszClassName = L"Space impact Class";

	RegisterClass(&m_WindowClass);

	m_WindowHandle = CreateWindowEx(0, L"Space impact Class", m_Name, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, m_Width, m_Height,
		NULL, NULL, hInstance, NULL);

	if (!m_WindowHandle)
	{
		std::cout << "Nu s-a putut creea fereastra" << std::endl;
		assert(m_WindowHandle);
	}

	ShowWindow(m_WindowHandle, SW_SHOW);
}

void Window::pollEvents()
{
	MSG msg = { };
	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

	if (msg.message == WM_QUIT)
	{
		m_isRunning = false;
	}

	TranslateMessage(&msg);
	DispatchMessage(&msg);
}