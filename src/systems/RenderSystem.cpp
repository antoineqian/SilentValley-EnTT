#include "RenderSystem.hpp"

void RenderSystem::draw(entt::registry &registry, sf::RenderWindow &window) const
{

    registry.view<MapLayer>().each(
        [&](auto &layer)
        { window.draw(layer); });

    registry.sort<Collision>(
        [](const auto &lhs, const auto &rhs)
        { return (lhs.hitBox.top + lhs.hitBox.height < rhs.hitBox.top + rhs.hitBox.height); });

    registry.view<Collision>().each(
        [&](auto entity, auto &col)
        {
            if (registry.any_of<sf::Sprite>(entity))
            {
                auto &sprite = registry.get<sf::Sprite>(entity);
                window.draw(sprite);
            }
            else if (registry.any_of<Animated>(entity))
            {
                auto &animated = registry.get<Animated>(entity);
                window.draw(animated.animatedSprite);
            }
        });
};
