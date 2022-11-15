#include "RaverSystem.hpp"

RaverSystem::RaverSystem(entt::registry &registry) : registry(registry)

{
    registry.on_update<Speaker>().connect<&RaverSystem::IdleFromToGoDance>(this);

    // registry.on_construct<GoDance>().connect<&GoDance::enter>();
    // registry.on_destroy<GoDance>().connect<&GoDance::exit>();

    // registry.on_construct<Idle>().connect<&Idle::enter>();
    // registry.on_destroy<Idle>().connect<&Idle::exit>();
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
        // auto view = registry.view<Raver, Idle>();
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
        // auto view = registry.view<Raver, GoDance>();
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
    // registry.view<Raver, GoDance>().each(
    for (auto entity : registry.view<GoDance>())
    {
        GoDance::execute(entity, registry);
    };

    for (auto entity : registry.view<Idle>())
    {
        Idle::execute(entity, registry);
    };
};
