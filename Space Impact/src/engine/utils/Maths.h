#pragma once

struct vec2
{
	float x = 0, y = 0;

	vec2() = default;
	vec2(float _x, float _y) : x(_x), y(_y) {}
};

struct vec3
{
	float x = 0, y = 0, z = 0;

	vec3() = default;
	vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct vec4
{
	float x = 0, y = 0, z = 0, w = 0;

	vec4() = default;
	vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) { }
};