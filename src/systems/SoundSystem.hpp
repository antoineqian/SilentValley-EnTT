#pragma once
#include "ISystem.hpp"
#include <SFML/Audio.hpp>
#include "../components/Speaker.hpp"
#include "../components/Collision.hpp"
class SoundSystem : public IUpdateSystem
{
public:
    SoundSystem(entt::registry &registry);
    void update(entt::registry &registry) override;
    static sf::FloatRect soundArea(entt::registry &registry);

private:
    sf::Music music;
    entt::observer observer;
    entt::registry &registry;
    void switchSoundSystem();
};