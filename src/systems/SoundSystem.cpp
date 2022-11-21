#include "SoundSystem.hpp"

SoundSystem::SoundSystem(entt::registry &registry) : registry(registry)
{
    observer.connect(registry, entt::collector.update<Speaker>());
    music.openFromFile("assets/sounds/08. Surrounded.flac");

    registry.on_update<Speaker>().connect<&SoundSystem::switchSoundSystem>(this);
}

void SoundSystem::switchSoundSystem()
{
    registry.view<Speaker>().each(
        [this](auto &speaker)
        {
            if (speaker.isActive && (music.getStatus() == sf::SoundSource::Status::Paused || music.getStatus() == sf::SoundSource::Status::Stopped))
            {
                music.play();
            }
            else if (!speaker.isActive && music.getStatus() == sf::SoundSource::Status::Playing)
            {
                music.pause();
            }
        });
}

void SoundSystem::update(entt::registry &registry)
{
}

sf::FloatRect SoundSystem::soundArea(entt::registry &registry)
{
    // TODO: Calculate area
    return sf::FloatRect{483, 281, 173, 91};
}