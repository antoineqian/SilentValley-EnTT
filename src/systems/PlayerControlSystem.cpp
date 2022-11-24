#include "PlayerControlSystem.hpp"

#include <iostream>

sf::Vector2f processVelocity();

void PlayerControlSystem::update(entt::registry &registry, sf::RenderWindow &window)
{
    // Keyboard
    // Direction
    sf::Vector2f velocity;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        velocity.x = -PLAYER_SPEED;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        velocity.x = PLAYER_SPEED;
    }
    else
        velocity.x = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        velocity.y = -PLAYER_SPEED;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))

    {
        velocity.y = PLAYER_SPEED;
    }
    else
        velocity.y = 0;

    if (std::abs(velocity.x) > 0 && std::abs(velocity.y) > 0)
    {
        velocity.x /= 1.4;
        velocity.y /= 1.4;
    }
    // Action
    bool spaceCmd{false};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        sf::Time elapsed = actionTimer.getElapsedTime();
        if (elapsed.asSeconds() > 1.f)
        {
            spaceCmd = true;
            actionTimer.restart();
        }
    }

    bool useSpeakers = false;
    registry.view<Moving, Collision, PlayerController>()
        .each(
            [&velocity, &useSpeakers, &spaceCmd, &registry](auto &moving, auto &collision, auto &controller)
            {
                moving.velocity = velocity;
                if (spaceCmd)
                {
                    auto faceBox = getFacePosition(collision.hitBox, moving.direction);
                    for (auto &&entity : registry.view<Speaker, Collision>())
                    {
                        if (faceBox.intersects(registry.get<Collision>(entity).hitBox))
                        {
                            useSpeakers = true;
                            break;
                        }
                    }
                }
            });

    if (useSpeakers)
    {
        registry.view<SoundRig>().each(
            [&registry](auto entity, auto &speaker)
            {
                registry.patch<SoundRig>(entity, [](auto &system)
                                         { system.isActive = !system.isActive; });
            });
    }
}

sf::FloatRect getFacePosition(sf::FloatRect box, Direction direction)
{
    switch (magic_enum::enum_integer(direction))
    {
    case magic_enum::enum_integer(Direction::up):
        return {box.left, box.top - 8, box.width, 8};
    case magic_enum::enum_integer(Direction::down):
        return {box.left, box.top + box.height, box.width, 8};
    case magic_enum::enum_integer(Direction::left):
        return {box.left - 8, box.top, 8, box.width};
    case magic_enum::enum_integer(Direction::right):
        return {box.left + box.width, box.top, 8, box.width};
    }
    return sf::FloatRect();
}
