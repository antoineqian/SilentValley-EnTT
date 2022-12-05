#pragma once
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
class IUpdateSystem
{
public:
	virtual void update(entt::registry &registry, sf::RenderWindow &window) = 0;
	virtual ~IUpdateSystem(){};
};

class IDrawSystem
{
public:
	virtual void draw(entt::registry &registry, sf::RenderWindow &window) = 0;
	virtual ~IDrawSystem(){};
};