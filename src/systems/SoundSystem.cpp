#include "SoundSystem.hpp"

#include <iostream>

SoundSystem::SoundSystem(entt::registry &registry) : jukebox("assets/sounds"), registry(registry)
{
    jukebox.requestAll();
    observer.connect(registry, entt::collector.update<Speaker>());
    registry.on_update<Speaker>().connect<&SoundSystem::switchSoundSystem>(this);
}

void SoundSystem::switchSoundSystem()
{
    registry.view<Speaker>().each(
        [this](auto &speaker)
        {
            if (speaker.isActive && !jukebox.playing())
            {
                std::cout << "Play\n";
                jukebox.play();
            }
            else if (!speaker.isActive && jukebox.playing())
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