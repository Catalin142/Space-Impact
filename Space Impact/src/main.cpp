#include "engine/Application.h"

#include "GameManager.h"
#include "engine/utils/SpriteManager.h"
#include "game/Player.h"
#include "game/BasicEnemy.h"
#include "engine/utils/Random.h"
#include "game/ShootingEnemy.h"

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
		m_ShootingEnemySprite = SpriteManager::loadSprite(L"res/ShootingEnemy.png");

	}

	virtual void onUpdate(float deltaTime) override
	{
		if (m_EnemyLastTime > m_EnemySpawnCooldown && m_Player->getScore() < 300)
		{
			CreateEntity<BasicEnemy>(m_EnemySprite, { 1600.0f, 100.0f + Random::Float() * (Window::Get()->getHeight() - 200.0f) }, { 140, 70 });
			m_EnemySpawnCooldown = 1.0f + Random::Float();
			m_EnemyLastTime = 0.0f;
		}
		
		else if (m_EnemyLastTime > m_EnemySpawnCooldown && m_Player->getScore() >= 300)
		{
			CreateEntity<ShootingEnemy>(m_ShootingEnemySprite, { 1600.0f, 100.0f + Random::Float() * (Window::Get()->getHeight() - 200.0f) }, { 125, 125 });
			m_EnemySpawnCooldown = 1.0f + Random::Float();
			m_EnemyLastTime = 0.0f;
		}

		GameManager::onUpdate();

		m_EnemyLastTime += deltaTime;
	}

private:
	Player* m_Player;

	std::shared_ptr<Sprite> m_EnemySprite;
	std::shared_ptr<Sprite> m_ShootingEnemySprite;
	float m_EnemySpawnCooldown = 1.0f;
	float m_EnemyLastTime;
};

int main()
{
	Application* game = new SpaceImpact(L"Space Impact", 1600U, 900U);
	game->Run();
}