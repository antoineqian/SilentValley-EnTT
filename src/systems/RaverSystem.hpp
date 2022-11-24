#pragma once
#include "ISystem.hpp"
#include <SFML/Graphics.hpp>
#include "../components/Raver.hpp"
#include "../components/Speaker.hpp"
#include "../components/state/RaverStates.hpp"

class RaverSystem : public IUpdateSystem
{
public:
    RaverSystem(entt::registry &registry);
    void update(entt::registry &registry, sf::RenderWindow &window) override;

private:
    void IdleFromToGoDance();
    entt::registry &registry;
    sf::Clock frameClock;
};
