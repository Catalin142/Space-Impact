#include "GraphicsContext.h"

#include <iostream>
#include <cassert>

#include "utils/Macros.h"

GraphicsContext* GraphicsContext::m_Instance = nullptr;

GraphicsContext::GraphicsContext(std::shared_ptr<Window>& window) : m_Window(window)
{
	if (FAILED(D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_Factory)));

	HRESULT res = S_OK;
	RECT rc;
	GetClientRect(m_Window->getHandle(), &rc);
	D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

	res = m_Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_Window->getHandle(), size, D2D1_PRESENT_OPTIONS_NONE),
		&m_RenderTarget);

	if (!SUCCEEDED(res))
	{
		std::cout << "Nu s-a putut creea context" << std::endl;
		assert(SUCCEEDED(res));
	}

	m_Instance = this;
}

GraphicsContext::~GraphicsContext()
{
	SAFE_RELEASE(m_RenderTarget);
	SAFE_RELEASE(m_Factory);
}

void GraphicsContext::onResize(uint16 width, uint16 height)
{
	RECT rc;
	GetClientRect(m_Window->getHandle(), &rc);

	D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

	m_RenderTarget->Resize(size);
	InvalidateRect(m_Window->getHandle(), NULL, FALSE);
}

void GraphicsContext::beginDraw()
{
	BeginPaint(m_Window->getHandle(), &m_PaintStruct);
	m_RenderTarget->BeginDraw();
}

void GraphicsContext::endDraw()
{
	m_RenderTarget->EndDraw();
	EndPaint(m_Window->getHandle(), &m_PaintStruct);
}

void GraphicsContext::clearScreen(float r, float g, float b)
{
	m_RenderTarget->Clear(D2D1::ColorF(r, g, b));
}
