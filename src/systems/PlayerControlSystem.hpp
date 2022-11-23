#pragma once
#include "../components/PlayerController.hpp"
#include "ISystem.hpp"
#include <SFML/Graphics.hpp>
#include "../components/Moving.hpp"
#include "../components/Speaker.hpp"
#include "../components/Collision.hpp"
#include "../components/PlayerController.hpp"
#include "../components/Animated.hpp"
#include "../constants.hpp"
#include <magic_enum.hpp>

class PlayerControlSystem : public IUpdateSystem
{
    void update(entt::registry &registry, sf::RenderWindow &window) override;
    sf::Clock actionTimer;
};
