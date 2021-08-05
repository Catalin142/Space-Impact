#pragma once
#include <memory>
#include "Win32Window.h"
#include "GraphicsContext.h"

struct Time
{
	static float deltaTime;
};

class Application
{
public:
	Application(const wchar_t* name, uint16 width, uint16 height);

	virtual void onCreate() { }
	virtual void onUpdate(float deltaTime) { } 
	virtual void onDestory() { }

	void Run();

	void ClearColor(float r, float g, float b) { R = r; G = g; B = b; }

protected:
	std::shared_ptr<Window> m_Window;
	std::shared_ptr<GraphicsContext> m_Context;

	float R = 0.0f, G = 0.0f, B = 0.0f;
};

/*
// Exemplu:
class yourApp : public Application
{
public:
	yourApp(const wchar_t* name, uint16 width, uint16 height) : Application(name, width, height) {}

	virtual void onCreate() override
	{
		// create
	}

	virtual void onUpdate() override
	{
		// update
	}

private:
	// resources
};

*/