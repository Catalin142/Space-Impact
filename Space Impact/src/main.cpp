#include "engine/Application.h"

#include "engine/utils/SpriteManager.h"
#include "engine/utils/Random.h"
#include "engine/gfx/TextRenderer.h"
#include "engine/utils/ColorFactory.h"
#include "engine/sound/SoundPlayer.h"

#include "game/Player.h"
#include "game/BasicEnemy.h"
#include "game/ShootingEnemy.h"
#include "game/Background.h"
#include "game/FirstBoss.h"

#include "GameManager.h"

#include <string>
#include <iostream>
#include <vector>

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
		m_NumbersSheet = SpriteManager::loadSprite(L"res/Numbers.png");
		m_CharSheet = SpriteManager::loadSprite(L"res/Characters.png");

		m_DeathAnimation = Animation(SpriteManager::loadSprite(L"res/Explosion.png"), 2, 200.0f, 90.0f);

		m_Player->setDeathAnimation(m_DeathAnimation);

		vec2 size = m_BackgroundSprite->getBitmapSize();
		size.x *= 1.3f;
		size.y *= 1.3f;
		m_Background[0] = CreateEntity<Background>(m_BackgroundSprite, { 0.0f, m_Window->getHeight() - size.y }, { size.x, size.y });
		m_Background[1] = CreateEntity<Background>(m_BackgroundSprite, { size.x, m_Window->getHeight() - size.y }, { size.x, size.y });
	}

	virtual void onUpdate(float deltaTime) override
	{
		if (m_State == ApplicationState::PLAY)
		{
			if (m_Player != nullptr)
			{
				if (m_EnemyLastTime > m_EnemySpawnCooldown && m_Player->getScore() < 300)
				{
					//auto enemy = CreateEntity<BasicEnemy>(m_EnemySprite, { (float)m_Window->getWidth(), 100.0f + Random::Float() * (Window::Get()->getHeight() - 200.0f) },
					//	{ 140, 90 });
					auto enemy = CreateEntity<ShootingEnemy>(m_ShootingEnemySprite, { (float)m_Window->getWidth(), 100.0f + Random::Float() * (Window::Get()->getHeight() - 200.0f) },
						{ 125, 125 });
					enemy->setDeathAnimation(m_DeathAnimation);
					m_EnemySpawnCooldown = 1.0f + Random::Float();
					m_EnemyLastTime = 0.0f;
				}

				else if (m_EnemyLastTime > m_EnemySpawnCooldown && m_Player->getScore() >= 300)
				{
					auto enemy = CreateEntity<ShootingEnemy>(m_ShootingEnemySprite, { (float)m_Window->getWidth(), 100.0f + Random::Float() * (Window::Get()->getHeight() - 200.0f) },
						{ 125, 125 });
					enemy->setDeathAnimation(m_DeathAnimation);
					m_EnemySpawnCooldown = 1.5f + Random::Float();
					m_EnemyLastTime = 0.0f;
				}

				if (m_Player->getScore() >= 900 && m_BossSpawned == false)
				{
					m_EnemyLastTime = 0.0f;
					m_EnemySpawnCooldown = 4.0f;
					m_Boss = CreateEntity<FirstBoss>(L"res/FirstBoss.png", { (float)m_Window->getWidth(), 100.0f + Random::Float() * (Window::Get()->getHeight() - 200.0f) },
						{ 300.0f, 300.0f });
					m_Boss->setDeathAnimation(m_DeathAnimation);

					m_BossSpawned++;
				}

				if (m_Player != nullptr)
				{
					if (m_Player->getStatus() == true)
					{
						auto score = std::to_string(m_Player->getScore());
						score.insert(0, 5 - score.size(), '0');

						TextRenderer::RenderNumbersFromPNG(m_NumbersSheet, score, { 1000.0f, 10.0f }, { 50.0f, 50.0f });
					}
				}

				if (m_BossSpawned == 1)
					if (m_Boss->isAlive() == false)
					{
						m_Player->m_LevelFinished = true;
						m_BossSpawned++;
					}

				if (m_Player->m_LevelFinished == true)
					TextRenderer::RenderTextFromPNG(m_CharSheet, "Level cleared", { m_Window->getWidth() / 2.0f - 6.5f * 75.0f, m_Window->getHeight() / 2.0f - 75.0f }, { 75.0f, 75.0f });

				GameManager::onUpdate();
				m_EnemyLastTime += deltaTime;

				if (m_Player->getStatus() == false)
					m_Player = nullptr;
			}
		}

		if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
		{
			if (m_State == ApplicationState::PAUSE)
				m_State = ApplicationState::PLAY;
			else m_State = ApplicationState::PAUSE;
		}

		else if (m_State == ApplicationState::PAUSE)
			TextRenderer::RenderTextFromPNG(m_CharSheet, "Pause", { m_Window->getWidth() / 2.0f - 2.5f * 75.0f, m_Window->getHeight() / 2.0f - 75.0f }, { 75.0f, 75.0f });
		
	}

private:
	Player* m_Player;
	Background* m_Background[2];
	FirstBoss* m_Boss = nullptr;

	std::shared_ptr<Sprite> m_BackgroundSprite;
	std::shared_ptr<Sprite> m_EnemySprite;
	std::shared_ptr<Sprite> m_ShootingEnemySprite;
	std::shared_ptr<Sprite> m_NumbersSheet;
	std::shared_ptr<Sprite> m_CharSheet;

	Animation m_DeathAnimation;

	float m_EnemySpawnCooldown = 1.0f;
	float m_EnemyLastTime = m_EnemySpawnCooldown;

	int m_BossSpawned = 0;
};

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	Application* game = new SpaceImpact(L"Space Impact", 1600U, 900U);
	game->Run();

	delete game;
	return 0;
}