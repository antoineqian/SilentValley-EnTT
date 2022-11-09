#pragma once
#include "ISystem.hpp"
#include "../components/Collision.hpp"
#include "../components/PlayerController.hpp"
#include "../components/Position.hpp"

class CollisionSystem : public IUpdateSystem
{
    void update(entt::registry &registry) override;
};