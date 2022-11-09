#pragma once
#include "../components/PlayerController.hpp"
#include "ISystem.hpp"
#include <SFML/Graphics.hpp>
#include "../components/Moving.hpp"
#include "../components/PlayerController.hpp"
#include "../components/Animated.hpp"
#include "../components/Position.hpp"
#include "../constants.hpp"

class PlayerControlSystem : public IUpdateSystem
{
    void update(entt::registry &registry) override;
};
