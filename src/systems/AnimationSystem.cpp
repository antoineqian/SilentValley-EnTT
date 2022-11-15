#include "AnimationSystem.hpp"

void AnimationSystem::update(entt::registry &registry)
{
    sf::Time frameTime = frameClock.restart();

    registry.view<Moving, Animated>().each(
        [&](auto &moving, auto &a)
        {
            a.animatedSprite.play(a.currentAnimation);
            a.animatedSprite.update(frameTime);
        });
}
