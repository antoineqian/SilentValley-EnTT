#include "SoundSystem.hpp"
#include <iostream>

SoundSystem::SoundSystem(entt::registry &registry) : jukebox("assets/sounds"), registry(registry)
{
    jukebox.requestAll();
    observer.connect(registry, entt::collector.update<Speaker>());
    auto entity = registry.create();
    registry.emplace<SoundRig>(entity);
    registry.on_update<SoundRig>().connect<&SoundSystem::switchSoundSystem>(this);
}

void SoundSystem::switchSoundSystem()
{
    registry.view<SoundRig>().each(
        [this](auto &system)
        {
            if (system.isActive && !jukebox.playing())
            {
                std::cout << "Play\n";
                jukebox.play();
            }
            else if (!system.isActive && jukebox.playing())
            {
                std::cout << "Stop\n";
                jukebox.stop();
            }
        });
}

void SoundSystem::update(entt::registry &registry)
{
    jukebox.update();
}

sf::FloatRect SoundSystem::soundArea(entt::registry &registry)
{
    // TODO: Calculate area
    return sf::FloatRect{483, 281, 173, 91};
}

void SoundSystem::select(const string &songName)
{
    std::cout << "Selected " << songName << '\n';
}