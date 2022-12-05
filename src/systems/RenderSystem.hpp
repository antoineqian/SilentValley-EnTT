#pragma once
#include <map>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include "ISystem.hpp"
#include "../../external/Layer.hpp"
#include "../components/Moving.hpp"
#include "../components/Collision.hpp"
#include "../components/Animated.hpp"
using std::string;

class RenderSystem : public IDrawSystem
{
public:
    void draw(entt::registry &registry, sf::RenderWindow &window);

};
