#pragma once
#include "ISystem.hpp"
#include <SFML/Graphics.hpp>
#include "../components/Animated.hpp"
#include "../components/Moving.hpp"

class AnimationSystem : public IUpdateSystem
{
    sf::Clock frameClock;
    void update(entt::registry &registry) override;
};