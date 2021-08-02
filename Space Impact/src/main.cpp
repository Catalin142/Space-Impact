#include "engine/Application.h"

#include "game/Player.h"
//int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)

class SpaceImpact : public Application
{
public:
	SpaceImpact(const wchar_t* name, uint16 width, uint16 height) : Application(name, width, height) {}

	virtual void onCreate() override
	{
		ClearColor(112.0f / 255.0f, 161.0f / 255.0f, 125.0f / 255.0f);
		m_Player = CreateEntity<Player>(L"res/Player.png", vec2(25, m_Window->getHeight() / 2), vec2(200, 150));
		m_Player->onCreate();
	}

	virtual void onUpdate() override
	{

	}

private:
	Player* m_Player;
	std::shared_ptr<Sprite> m_Sprite;
};

int main()
{
	Application* game = new SpaceImpact(L"Space Impact", 1600U, 900U);
	game->Run();
}