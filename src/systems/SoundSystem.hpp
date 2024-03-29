#pragma once
#include "ISystem.hpp"
#include "../components/Speaker.hpp"
#include "../components/Collision.hpp"
#include "../managers/Jukebox.hpp"
#include <string>
using std::string;
class SoundSystem : public IUpdateSystem
{
public:
    SoundSystem(entt::registry &registry);
    void update(entt::registry &registry, sf::RenderWindow &window) override;
    static sf::FloatRect soundArea(entt::registry &registry);
    void select(size_t index, const string &songName);

private:
    Jukebox jukebox;
    entt::observer observer;
    entt::registry &registry;
    void switchSoundSystem();
};