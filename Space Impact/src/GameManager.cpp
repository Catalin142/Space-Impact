#include "GameManager.h"

#include "game/Player.h"
#include "game/BasicEnemy.h"
#include "game/ShootingEnemy.h"

Entity* GameManager::m_Player = nullptr;
std::vector<Entity*> GameManager::m_PlayerBullets;
std::vector<Entity*> GameManager::m_EnemyBullets;
std::vector<Entity*> GameManager::m_Enemies;

void GameManager::onUpdate()
{
	if (m_Player != nullptr)
	{
		for (auto& enemy : m_Enemies)
		{
			if (checkCollision(m_Player, enemy))
			{
				if (enemy->m_isCollidable == true)
				{
					static_cast<Player*>(m_Player)->takeDamage(1);
					if (enemy->getTag() == "BasicEnemy")
						static_cast<BasicEnemy*>(enemy)->takeDamage(100);

					else if (enemy->getTag() == "ShootingEnemy")
						static_cast<ShootingEnemy*>(enemy)->takeDamage(100);

					enemy->m_isCollidable = false;
				}
			}

			for (auto& bullet : m_PlayerBullets)
			{
				if (checkCollision(enemy, bullet))//&& bullet->getStatus() == true)
				{
					DestroyEntity(bullet);
					if (enemy->getTag() == "BasicEnemy")
					{
						static_cast<BasicEnemy*>(enemy)->takeDamage(1);
						if (static_cast<BasicEnemy*>(enemy)->isAlive() == false)
							static_cast<Player*>(m_Player)->addScore(25);
					}
					else if (enemy->getTag() == "ShootingEnemy")
					{
						static_cast<ShootingEnemy*>(enemy)->takeDamage(1);

						if (static_cast<ShootingEnemy*>(enemy)->isAlive() == false)
							static_cast<Player*>(m_Player)->addScore(35);
					}

				}

			}
		}

		for (auto& bullet : m_EnemyBullets)
		{
			if (checkCollision(m_Player, bullet))
			{
				static_cast<Player*>(m_Player)->takeDamage(1);
				DestroyEntity(bullet);
			}

			for (auto& pBullet : m_PlayerBullets)
			{
				if (checkCollision(bullet, pBullet))
				{
					DestroyEntity(bullet);
					DestroyEntity(pBullet);
				}
			}
		}

		if (m_Player->getStatus() == false)
			m_Player = nullptr;
	}


	checkContainterForDeadEntites(m_Enemies);
	checkContainterForDeadEntites(m_PlayerBullets);
	checkContainterForDeadEntites(m_EnemyBullets);
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
