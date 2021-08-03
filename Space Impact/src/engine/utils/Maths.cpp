#include "Maths.h"

#include <cmath>

vec2 moveTowards(const vec2& current, const vec2& target, float speed)
{
	vec2 tract = { target.x - current.x, target.y - current.y };
	float remainingDistance = sqrt(tract.x * tract.x + tract.y * tract.y);
	if (remainingDistance <= speed || remainingDistance == 0.0f)
		return target;

	vec2 tractDiv = { tract.x / remainingDistance, tract.y / remainingDistance };
	vec2 sum = { current.x + tractDiv.x * speed, current.y + tractDiv.y * speed };
	return (sum);
}