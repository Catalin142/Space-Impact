#pragma once
#include "../engine/entity/Entity.h"
#include "../engine/utils/Maths.h"
#include "ShootingEnemy.h"

class FirstBoss : public ShootingEnemy
{
public:
	FirstBoss(const wchar_t* filepath, const vec2& pos = { 0, 0 }, const vec2& size = { 1, 1 });

	virtual void onUpdate(float deltaTime) override;

private:
	int m_Direction = 1;
};