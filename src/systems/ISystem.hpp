#pragma once
#include "entt.hpp"
// #include <execution>

class IUpdateSystem
{
public:
	virtual void update(entt::registry& registry) = 0;
	virtual ~IUpdateSystem(){};
};