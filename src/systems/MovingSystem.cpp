#include "MovingSystem.hpp"

void MovingSystem::update(entt::registry &registry)
{
    registry.view<Moving, Animated, Position, Collision>().each(
        [](auto &moving, auto &animated, auto &position, auto &collision)
        {
            animated.animatedSprite.move(moving.velocity);
            position.position = animated.animatedSprite.getPosition();
            auto box = animated.animatedSprite.getGlobalBounds();
            auto actualBox = sf::FloatRect{box.left, box.top + 12, TILE_SIZE, PLAYER_HEIGHT};
            collision.hitBox = shrinkToHitBox(actualBox);
        });
}