#pragma once
#include "../gfx/Sprite.h"
#include "../utils/Maths.h"

#include <memory>

class Entity
{
public:
	Entity(const wchar_t* filepath, const vec2& pos = { 0, 0 }, const vec2& size = { 1, 1 });
	Entity(const std::shared_ptr<Sprite>& sprite, const vec2& pos = { 0, 0 }, const vec2& size = { 1, 1 });

	virtual void onCreate() { }
	virtual void onUpdate(float deltaTime) { }
	void onDraw();

	bool& getStatus() { return m_isAlive; }

protected:
	std::shared_ptr<Sprite> m_Sprite;
	vec2 m_Position = { 0, 0 };
	vec2 m_Size = { 1, 1 };

	bool m_isAlive = true;
	// TODO bool isCollidable = false 
};

template <typename T>
T* CreateEntity(const wchar_t* filepath, const vec2& pos = { 0, 0 }, const vec2& size = { 1, 1 })
{
	T* ent = new T(filepath, pos, size);
	return ent;
}

template <typename T>
T* CreateEntity(const std::shared_ptr<Sprite>& spr, const vec2& pos = { 0, 0 }, const vec2& size = { 1, 1 })
{
	T* ent = new T(spr, pos, size);
	return ent;
}

/*
// Exemplu:
class yourEntity : public Entity
{
public:
	yourEntity(const wchar_t* filepath, const vec2& pos = { 0, 0 }, const vec2& size = { 1, 1 });

	virtual void onCreate() override {}
	virtual void onUpdate(float deltaTime) override;

private:

};
*/