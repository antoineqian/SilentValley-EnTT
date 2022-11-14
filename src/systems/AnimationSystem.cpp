#include "AnimationSystem.hpp"

void AnimationSystem::update(entt::registry &registry)
{
    sf::Time frameTime = frameClock.restart();

    registry.view<Moving, Animated>().each(
        [&](auto &moving, auto &a)
        {
            // auto &vel = moving.velocity;
            // auto &dir = moving.direction;
            // if (vel.x != 0 || vel.y != 0)
            //     a.currentAnimation = a.animations[string(magic_enum::enum_name(direction)) + string("_walking")];

            // if (vel.x < 0)
            // {
            //     a.currentAnimation = a.animations["left_walking"];
            // }
            // else if (vel.x > 0)
            // {
            //     a.currentAnimation = a.animations["right_walking"];
            // }
            // else if (vel.y < 0)
            // {
            //     a.currentAnimation = a.animations["up_walking"];
            // }
            // else if (vel.y > 0)
            // {
            //     a.currentAnimation = a.animations["down_walking"];
            // }

            a.animatedSprite.play(a.currentAnimation);

            // if (vel.x == 0 && vel.y == 0)
            // {
            //     a.animatedSprite.stop();
            // }
            a.animatedSprite.update(frameTime);
        });
}
