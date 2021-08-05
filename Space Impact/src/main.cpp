#include "engine/Application.h"

#include "engine/utils/SpriteManager.h"
#include "engine/utils/Random.h"
#include "engine/gfx/TextRenderer.h"
#include "engine/utils/ColorFactory.h"

#include "game/Player.h"
#include "game/BasicEnemy.h"
#include "game/ShootingEnemy.h"
#include "game/Background.h"
#include "game/FirstBoss.h"

#include "GameManager.h"

#include <string>
#include <iostream>
#include <vector>
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
		m_BackgroundSprite = SpriteManager::loadSprite(L"res/Background.png");
		m_DeathAnimation = Animation(SpriteManager::loadSprite(L"res/Explosion.png"), 2, 200.0f, 90.0f);

		m_Player->setDeathAnimation(m_DeathAnimation);

		vec2 size = m_BackgroundSprite->getBitmapSize();
		size.x *= 1.3f;
		size.y *= 1.3f;
		m_Background[0] = CreateEntity<Background>(m_BackgroundSprite, { 0.0f, m_Window->getHeight() - size.y }, { size.x, size.y });
		m_Background[1] = CreateEntity<Background>(m_BackgroundSprite, { size.x, m_Window->getHeight() - size.y }, { size.x, size.y });

		ColorFactory::createColor("Negru", 0.0f, 0.0f, 0.0f);
		TextFormatManager::createFormat("Font principal", L"ArcadeClassic", 100.0f);
	}

	virtual void onUpdate(float deltaTime) override
	{
		if (m_EnemyLastTime > m_EnemySpawnCooldown && m_Player->getScore() < 300)
		{
			auto enemy = CreateEntity<BasicEnemy>(m_EnemySprite, { (float)m_Window->getWidth(), 100.0f + Random::Float() * (Window::Get()->getHeight() - 200.0f) }, 
				{ 140, 90 });
			enemy->setDeathAnimation(m_DeathAnimation);
			m_EnemySpawnCooldown = 1.0f + Random::Float();
			m_EnemyLastTime = 0.0f;
		}
		
		else if (m_EnemyLastTime > m_EnemySpawnCooldown && m_Player->getScore() >= 300)
		{
			auto enemy = CreateEntity<ShootingEnemy>(m_ShootingEnemySprite, {  (float)m_Window->getWidth(), 100.0f + Random::Float() * (Window::Get()->getHeight() - 200.0f) },
				{ 125, 125 });
			enemy->setDeathAnimation(m_DeathAnimation);
			m_EnemySpawnCooldown = 1.5f + Random::Float();
			m_EnemyLastTime = 0.0f;
		}

		if (m_Player->getScore() >= 200 && m_BossSpawned == false)
		{
			m_EnemyLastTime = 0.0f;
			m_EnemySpawnCooldown = 4.0f;
			CreateEntity<FirstBoss>(L"res/FirstBoss.png", {(float)m_Window->getWidth(), 100.0f + Random::Float() * (Window::Get()->getHeight() - 200.0f)}, {300.0f, 300.0f});

			m_BossSpawned = true;
		}

		if (m_Player->getStatus() == true)
		{
			auto score = std::to_wstring(m_Player->getScore());
			score.insert(0, 5 - score.size(), L'0');

			TextRenderer::RenderString(score.c_str(), { 1100.0f, 10.0f }, TextFormatManager::getFormat("Font principal"),
				ColorFactory::getColor("Negru")); \
		}

		GameManager::onUpdate();

		m_EnemyLastTime += deltaTime;
	}

private:
	Player* m_Player;
	Background* m_Background[2];

	std::shared_ptr<Sprite> m_BackgroundSprite;
	std::shared_ptr<Sprite> m_EnemySprite;
	std::shared_ptr<Sprite> m_ShootingEnemySprite;

	Animation m_DeathAnimation;

	float m_EnemySpawnCooldown = 1.0f;
	float m_EnemyLastTime;

	bool m_BossSpawned = false;
};

int main()
{
	Application* game = new SpaceImpact(L"Space Impact", 1600U, 900U);
	game->Run();

	delete game;
	return 0;
}