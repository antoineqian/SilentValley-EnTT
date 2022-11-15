#include "MovingSystem.hpp"
#include <iostream>

void MovingSystem::update(entt::registry &registry)
{
    registry.view<Moving, Animated, Collision>().each(
        [](auto &moving, auto &animated, auto &collision)
        {
            animated.animatedSprite.move(moving.velocity);
            auto box = animated.animatedSprite.getGlobalBounds();
            auto actualBox = sf::FloatRect{box.left, box.top + 12, TILE_SIZE, PLAYER_HEIGHT};
            collision.hitBox = shrinkToHitBox(actualBox);

            // auto pos = animated.animatedSprite.getPosition();
            // std::cout << pos.x << " " << pos.y << '\n';

            Direction direction{Direction::nodir};
            if (moving.velocity.x < 0)
            {
                direction = Direction::left;
            }
            else if (moving.velocity.x > 0)
            {
                direction = Direction::right;
            }
            if (moving.velocity.y < 0)
            {
                direction = Direction::up;
            }
            else if (moving.velocity.y > 0)
            {
                direction = Direction::down;
            }
            if (magic_enum::enum_integer(direction) != magic_enum::enum_integer(Direction::nodir))
            {
                moving.direction = direction;
                animated.currentAnimation = animated.animations[string(magic_enum::enum_name(direction)) + string("_walking")];
            }
        });
}