#pragma once
#include "ISystem.hpp"

class GUISystem : public IDrawSystem
{
public:
    void draw(entt::registry &registry, sf::RenderWindow &window) const override;
};
