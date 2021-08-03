#include "GameManager.h"

#include "Player.h"
#include "BasicEnemy.h"

Entity* GameManager::m_Player = nullptr;
std::vector<Entity*> GameManager::m_PlayerBullets;
std::vector<Entity*> GameManager::m_EnemyBullets;
std::vector<Entity*> GameManager::m_Enemies;

void GameManager::onUpdate()
{
	for (auto& enemy : m_Enemies)
	{
		if (checkCollision(m_Player, enemy))
		{
			//static_cast<Player*>(m_Player)->takeDamage(1);
			DestroyEntity(enemy);
		}

		for (auto& bullet : m_PlayerBullets)
		{
			if (checkCollision(enemy, bullet))//&& bullet->getStatus() == true)
			{
				DestroyEntity(bullet);
				if (enemy->getTag() == "BasicEnemy")
					static_cast<BasicEnemy*>(enemy)->takeDamage(1);
			}
		}
	}

	checkContainterForDeadEntites(m_Enemies);
	checkContainterForDeadEntites(m_PlayerBullets);
}

void GameManager::setPlayer(Entity* player)
{
	m_Player = player;
}

void GameManager::pushBackPlayerBullet(Entity* entity)
{
	m_PlayerBullets.push_back(entity);
}

void GameManager::pushBackEnemy(Entity* entity)
{
	m_Enemies.push_back(entity);
}

void GameManager::pushBackEnemyBullet(Entity* entity)
{
	m_EnemyBullets.push_back(entity);
}

void GameManager::checkContainterForDeadEntites(std::vector<Entity*>& container)
{
	container.erase(std::remove_if(container.begin(), container.end(), [](Entity* enemy) { return !enemy->getStatus(); }), container.end());
}
