#include "RaverSystem.hpp"

RaverSystem::RaverSystem(entt::registry &registry) : registry(registry)

{
    registry.on_update<Speaker>().connect<&RaverSystem::IdleFromToGoDance>(this);
}

// void switchState(entt::entity &entity, type from,)
// {
// }

void RaverSystem::IdleFromToGoDance()
{
    auto aSpeaker = registry.view<Speaker>().begin();
    bool speakerOn = registry.get<Speaker>(*aSpeaker).isActive;
    if (speakerOn)
    {
        for (auto entity : registry.view<Raver, Idle>())
        {
            registry.remove<Idle>(entity);
            registry.emplace<GoDance>(entity);
            Idle::exit(entity, registry);
            GoDance::enter(entity, registry);
        };
    }
    else
    {
        for (auto entity : registry.view<Raver, GoDance>())
        {
            registry.remove<GoDance>(entity);
            registry.emplace<Idle>(entity);
            GoDance::exit(entity, registry);
            Idle::enter(entity, registry);
        };
    }
}

void RaverSystem::update(entt::registry &registry)
{
    for (auto entity : registry.view<GoDance>())
    {
        GoDance::execute(entity, registry);
    };

    for (auto entity : registry.view<Idle>())
    {
        Idle::execute(entity, registry);
    };
};
