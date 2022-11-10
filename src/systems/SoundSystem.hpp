#pragma once
#include "ISystem.hpp"
#include <SFML/Audio.hpp>
#include "../components/Speaker.hpp"

class SoundSystem : public IUpdateSystem
{
public:
    SoundSystem(entt::registry &registry);
    void update(entt::registry &registry) override;

private:
    sf::Music music;
    entt::observer observer;
};