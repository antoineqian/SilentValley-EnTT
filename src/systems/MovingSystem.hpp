#pragma once
#include "ISystem.hpp"
#include "../components/Moving.hpp"
#include "../components/Animated.hpp"
#include "../components/Collision.hpp"
#include "../constants.hpp"

/**
 * Moves entities regardless of their graphical representations and keeps their position up to date
 */
class MovingSystem : public IUpdateSystem
{
    void update(entt::registry &registry) override;
};