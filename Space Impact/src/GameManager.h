#pragma once
#include "engine/entity/Entity.h"
#include "engine/utils/SpriteManager.h"
#include "engine/gfx/Animation.h"

#include <vector>
#include <memory>

class GameManager
{
public:
	static void onUpdate();

	static void setPlayer(Entity* player);
	static void pushBackPlayerBullet(Entity* entity);

	static void pushBackEnemy(Entity* entity);
	static void pushBackEnemyBullet(Entity* entity);

private:
	static Entity* m_Player;
	static std::vector<Entity*> m_PlayerBullets;
	static std::vector<Entity*> m_EnemyBullets;
	static std::vector<Entity*> m_Enemies;

private:
	GameManager() = default;
	~GameManager() = default;

	static void checkContainterForDeadEntites(std::vector<Entity*>& container);

};