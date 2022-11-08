#pragma once
#include "../components/PlayerController.hpp"
#include "ISystem.hpp"
#include <SFML/Graphics.hpp>
#include "../components/Moving.hpp"
#include "../components/PlayerController.hpp"
#include "../constants.hpp"

class PlayerControlSystem  : public IUpdateSystem {
 void update(entt::registry& registry) override;
};

// void PlayerControlSystem::update(entt::registry& registry){
//     registry.view<Moving, PlayerController, sf::Sprite>().each([](auto& moving, auto& controller, auto& sprite)
//         {
//             moving.velocity = processVelocity();
//             sprite.setPosition(moving.velocity.x, moving.velocity.y);
//         });
// }