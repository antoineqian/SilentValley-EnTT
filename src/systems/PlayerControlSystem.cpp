#include "PlayerControlSystem.hpp"

#include <iostream>

sf::Vector2f processVelocity();

void PlayerControlSystem::update(entt::registry &registry)
{
    // Keyboard
    // Direction
    sf::Vector2f velocity;
    Direction direction{Direction::nodir};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        velocity.x = -PLAYER_SPEED;
        // direction = Direction::left;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        velocity.x = PLAYER_SPEED;
        // direction = Direction::right;
    }
    else
        velocity.x = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        velocity.y = -PLAYER_SPEED;
        // direction = Direction::up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))

    {
        velocity.y = PLAYER_SPEED;
        // direction = Direction::down;
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
                // if (magic_enum::enum_integer(direction) != magic_enum::enum_integer(Direction::nodir))
                // {
                //     moving.direction = direction;
                // }
                if (spaceCmd)
                {
                    auto faceBox = getFacePosition(collision.hitBox, moving.direction);
                    registry.view<Speaker, Collision>().each(
                        [&useSpeakers, &faceBox](auto &speaker, auto &collision2)
                        {
                            if (faceBox.intersects(collision2.hitBox))
                            {
                                useSpeakers = true;
                            }
                        });
                }
            });

    if (useSpeakers)
    {
        registry.view<Speaker>().each(
            [&registry](auto entity, auto &speaker)
            {
                registry.patch<Speaker>(entity, [](auto &speaker)
                                        { speaker.isActive = !speaker.isActive; });
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
