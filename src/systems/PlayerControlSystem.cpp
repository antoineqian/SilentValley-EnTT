#include "PlayerControlSystem.hpp"

sf::Vector2f processVelocity();

void PlayerControlSystem::update(entt::registry &registry)
{
    registry.view<Moving, PlayerController>().each(
        [](auto &moving, auto &controller)
        {
            moving.velocity = processVelocity();
        });
}

sf::Vector2f processVelocity()
{
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
    return velocity;
}