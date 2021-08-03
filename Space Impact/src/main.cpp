#include "engine/Application.h"

#include "game/Player.h"
#include "game/BasicEnemy.h"
#include "engine/utils/Random.h"
#include "game/GameManager.h"

//int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)

class SpaceImpact : public Application
{
public:
	SpaceImpact(const wchar_t* name, uint16 width, uint16 height) : Application(name, width, height) {}

	virtual void onCreate() override
	{
		ClearColor(112.0f / 255.0f, 161.0f / 255.0f, 125.0f / 255.0f);
		m_Player = CreateEntity<Player>(L"res/Player.png", vec2(25, m_Window->getHeight() / 2), vec2(175, 125));
		m_EnemySprite = SpriteManager::loadSprite(L"res/Enemy.png");

	}

	virtual void onUpdate(float deltaTime) override
	{
		if (m_EnemyLastTime > m_EnemySpawnCooldown)
		{
			CreateEntity<BasicEnemy>(m_EnemySprite, { 1600.0f, 450.0f }, { 100, 75 });
			m_EnemySpawnCooldown = 1.0f + Random::Float();
			m_EnemyLastTime = 0.0f;
		}

		GameManager::onUpdate();

		m_EnemyLastTime += deltaTime;
	}

private:
	Player* m_Player;
	BasicEnemy* m_Enemy;

	std::shared_ptr<Sprite> m_EnemySprite;
	float m_EnemySpawnCooldown = 1.0f;
	float m_EnemyLastTime;
};

int main()
{
	Application* game = new SpaceImpact(L"Space Impact", 1600U, 900U);
	game->Run();
}