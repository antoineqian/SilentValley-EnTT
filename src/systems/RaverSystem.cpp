#include "RaverSystem.hpp"

RaverSystem::RaverSystem(entt::registry &registry) : registry(registry)

{
    registry.on_update<Speaker>().connect<&RaverSystem::IdleFromToGoDance>(this);

    // registry.on_construct<GoDance>().connect<&GoDance::enter>();
    // registry.on_destroy<GoDance>().connect<&GoDance::exit>();

    // registry.on_construct<Idle>().connect<&Idle::enter>();
    // registry.on_destroy<Idle>().connect<&Idle::exit>();
}

void RaverSystem::IdleFromToGoDance()
{
    auto aSpeaker = registry.view<Speaker>().begin();
    bool speakerOn = registry.get<Speaker>(*aSpeaker).isActive;
    if (speakerOn)
    {
        registry.view<Raver, Idle>().each(
            [this](auto entity, auto &raver, auto &state)
            {
                registry.remove<Idle>(entity);
                registry.emplace<GoDance>(entity);
                Idle::exit(entity, registry);
                GoDance::enter(entity, registry);
            });
    }
    else
    {
        registry.view<Raver, GoDance>().each(
            [this](auto entity, auto &raver, auto &state)
            {
                registry.remove<GoDance>(entity);
                registry.emplace<Idle>(entity);
                GoDance::exit(entity, registry);
                Idle::enter(entity, registry);
            });
    }
}

void RaverSystem::update(entt::registry &registry)
{
    registry.view<Raver, GoDance>().each(
        [&registry](auto entity, auto &raver, auto &state)
        {
            GoDance::execute(entity, registry);
        });

    registry.view<Raver, Idle>().each(
        [&registry](auto entity, auto &raver, auto &state)
        {
            Idle::execute(entity, registry);
        });
};

// void Raver::changeState(std::unique_ptr<State> state)
// {
//     auto ptr = getptr();

//     // call the exit method of the existing state
//     currentState->exit(ptr);

//     // change state to the new state
//     currentState = std::move(state);

//     // call the entry method of the new state
//     currentState->enter(ptr);
// }
