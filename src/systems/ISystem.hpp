#pragma once
#include "entt.hpp"
#include <SFML/Graphics.hpp>
class IUpdateSystem
{
public:
	virtual void update(entt::registry &registry) = 0;
	virtual ~IUpdateSystem(){};
};

class IDrawSystem
{
public:
	virtual void draw(entt::registry &registry, sf::RenderWindow &window) const = 0;
	virtual ~IDrawSystem(){};
};