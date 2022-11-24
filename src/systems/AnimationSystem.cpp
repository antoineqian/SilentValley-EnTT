#include "AnimationSystem.hpp"

void AnimationSystem::update(entt::registry &registry, sf::RenderWindow &window)
{
    sf::Time frameTime = frameClock.restart();

    registry.view<Animated>().each(
        [&](auto &a)
        {
            a.animatedSprite.play(a.currentAnimation);
            a.animatedSprite.update(frameTime);
        });
}
