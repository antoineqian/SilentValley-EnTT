#include "SoundSystem.hpp"

SoundSystem::SoundSystem(entt::registry &registry)
{
    // entt::observer observer{registry, entt::collector.update<Speaker>()};
    observer.connect(registry, entt::collector.update<Speaker>());
    music.openFromFile("assets/sounds/08. Surrounded.flac");
}

void SoundSystem::update(entt::registry &registry)
{
    auto pEntity = observer.begin();

    if (pEntity != observer.end())
    {
        auto &speaker = registry.get<Speaker>(*pEntity);
        if (speaker.isActive && (music.getStatus() == sf::SoundSource::Status::Paused || music.getStatus() == sf::SoundSource::Status::Stopped))
        {
            music.play();
        }
        else if (!speaker.isActive && music.getStatus() == sf::SoundSource::Status::Playing)
        {
            music.pause();
        }
        // break;
        // });
        observer.clear();
    }

    // });
    // registry.view<Speaker>().each(
    //     [](auto &speaker)
    //     {
    //         if (speaker.isActive && (music.getStatus() == sf::SoundSource::Status::Paused || music.getStatus() == sf::SoundSource::Status::Stopped))
    //         {
    //             music.play();
    //         }
    //         else if (!speaker.isActive && music.getStatus() == sf::SoundSource::Status::Playing)
    //         {
    //             music.pause();
    //         }
    //         break;
    //     });
}
