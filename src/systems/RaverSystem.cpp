#include "RaverSystem.hpp"
#include <iostream>

RaverSystem::RaverSystem(entt::registry &registry) : registry(registry)

{
    registry.on_update<Speaker>().connect<&RaverSystem::IdleFromToGoDance>(this);
}

template <typename T, typename U>
void switchState(const entt::entity &entity, entt::registry &registry)
{
    registry.remove<T>(entity);
    registry.emplace<U>(entity);
    T::exit(entity, registry);
    U::enter(entity, registry);
}

void RaverSystem::IdleFromToGoDance()
{
    auto aSpeaker = registry.view<Speaker>().begin();
    bool speakerOn = registry.get<Speaker>(*aSpeaker).isActive;
    if (speakerOn)
    {
        for (auto &&entity : registry.view<Raver, Idle>())
        {
            switchState<Idle, GoDance>(entity, registry);
        };
    }
    else
    {
        for (auto entity : registry.view<Raver, GoDance>())
        {
            switchState<GoDance, Idle>(entity, registry);
        };
    }
}

void RaverSystem::update(entt::registry &registry)
{
    auto frameTime = frameClock.restart().asSeconds() / 60;

    for (auto entity : registry.view<Raver, GoDance>())
    {
        auto &raver = registry.get<Raver>(entity);

        raver.thirst -= frameTime;
        if (raver.thirst > 0)
        {
            std::cout << raver.thirst << "\n";
            GoDance::execute(entity, registry);
        }
        else
        {
            std::cout << raver.thirst << "\n";
            switchState<GoDance, GoDrink>(entity, registry);
        }
    };

    for (auto entity : registry.view<Idle>())
    {
        Idle::execute(entity, registry);
    };
};
