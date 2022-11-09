#include "MovingSystem.hpp"

void MovingSystem::update(entt::registry &registry)
{
    registry.view<Moving, Animated, Position>().each(
        [](auto &moving, auto &animated, auto &position)
        {
            animated.animatedSprite.move(moving.velocity);
            position.position = animated.animatedSprite.getPosition();
        });
}