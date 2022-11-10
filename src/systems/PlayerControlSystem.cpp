#include "PlayerControlSystem.hpp"

sf::Vector2f processVelocity();

void PlayerControlSystem::update(entt::registry &registry)
{
    // Keyboard
    // Direction
    sf::Vector2f velocity;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        velocity.x = -PLAYER_SPEED;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        velocity.x = PLAYER_SPEED;
    else
        velocity.x = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        velocity.y = -PLAYER_SPEED;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        velocity.y = PLAYER_SPEED;
    else
        velocity.y = 0;

    if (std::abs(velocity.x) > 0 && std::abs(velocity.y) > 0)
    {
        velocity.x /= 1.4;
        velocity.y /= 1.4;
    }
    // Action
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        // auto speakers = getSpeakers();
        // bool useSpeakers = false;
        // for (auto &&speaker : speakers)
        // {
        //     if (getPlayer()->getFacePosition().intersects(speaker->getHitBox()))
        //         useSpeakers = true;
        // }

        // if (useSpeakers)
        // {
        //     for (auto &&speaker : speakers)
        //     {
        //         speaker->switchState();
        //     }
        // }
    }

    registry.view<Moving, PlayerController>()
        .each(
            [&velocity](auto &moving, auto &controller)
            {
                moving.velocity = velocity;
            });
}
