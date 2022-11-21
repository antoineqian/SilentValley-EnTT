#pragma once
#include "ISystem.hpp"
#include "../components/Speaker.hpp"
#include "../components/Collision.hpp"
#include "../managers/Jukebox.hpp"

class SoundSystem : public IUpdateSystem
{
public:
    SoundSystem(entt::registry &registry);
    void update(entt::registry &registry) override;
    static sf::FloatRect soundArea(entt::registry &registry);

private:
    Jukebox jukebox;
    entt::observer observer;
    entt::registry &registry;
    void switchSoundSystem();
};