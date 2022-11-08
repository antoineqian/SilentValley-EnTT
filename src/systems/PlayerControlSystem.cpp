#include "PlayerControlSystem.hpp"

#include <iostream>
using std::cout;

sf::Vector2f processVelocity();


void PlayerControlSystem::update(entt::registry& registry){
    registry.view<Moving, PlayerController, sf::Sprite>().each([](auto& moving, auto& controller, auto& sprite)
        {
            moving.velocity = processVelocity();
            sprite.setPosition(moving.velocity.x, moving.velocity.y);
        });
}

sf::Vector2f processVelocity(){
    sf::Vector2f velocity;
    // bool noKeyWasPressed = true;
    // sf::Time frameTime = frameClock.restart();
    // auto hitBox = getHitBox();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        // std::cout << "Left\n";
        // noKeyWasPressed = false;
        // direction = Direction::left;
        // currentAnimation = animations[string(magic_enum::enum_name(direction)) + string("_walking")];

        // Left arrow key pressed - move to the left
        // Unless the Player has gone past the left hand side
        // if (hitBox.left >= 0)
        velocity.x = -PLAYER_SPEED;
        // else
            // velocity.x = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        // noKeyWasPressed = false;
        // direction = Direction::right;
        // currentAnimation = animations[string(magic_enum::enum_name(direction)) + string("_walking")];

        // Similarly for the right arrow
        // if (hitBox.left + hitBox.width <= constants::window_width)
        velocity.x = PLAYER_SPEED;
        // else
            // velocity.x = 0;
    }
    else
    {
        velocity.x = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        // noKeyWasPressed = false;
        // direction = Direction::up;
        // currentAnimation = animations[string(magic_enum::enum_name(direction)) + string("_walking")];
        // if (hitBox.top >= 0)
        velocity.y = -PLAYER_SPEED;
        // else
        //     velocity.y = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        // noKeyWasPressed = false;
        // direction = Direction::down;
        // currentAnimation = animations[string(magic_enum::enum_name(direction)) + string("_walking")];
        // if (hitBox.top + hitBox.height <= constants::window_height)
        velocity.y = PLAYER_SPEED;
        // else
        //     velocity.y = 0;
    }
    else
    {
        velocity.y = 0;
    }
    // animatedSprite.play(currentAnimation);
    // animatedSprite.move(velocity);
    // if (noKeyWasPressed)
    // {
    //     animatedSprite.stop();
    // }
    // animatedSprite.update(frameTime);
    return velocity;
}