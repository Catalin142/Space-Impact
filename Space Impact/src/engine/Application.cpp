#include "Application.h"

#include <chrono>

#include "utils/Random.h"

float Time::deltaTime = 0.0f;

Application::Application(const wchar_t* name, uint16 width, uint16 height)
{
	m_Window = std::make_shared<Window>(name, width, height);
	m_Context = std::make_shared<GraphicsContext>(m_Window);
}

void Application::Run()
{
	Random::Init();
	onCreate();
	std::chrono::steady_clock::time_point timeNow = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point oldTime = timeNow;

	while (m_Window->isRunning())
	{
		timeNow = std::chrono::high_resolution_clock::now();
		Time::deltaTime = std::chrono::duration<float>(timeNow - oldTime).count();

		m_Context->beginDraw();
		m_Context->clearScreen(R, G, B);

		EntityManager::updateEntities(Time::deltaTime);
		onUpdate(Time::deltaTime);
		EntityManager::checkForDeadEntities();

		m_Context->endDraw();
		
		m_Window->pollEvents();
		oldTime = timeNow;
	}
}
