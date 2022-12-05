#ifndef RAVER_STATES_H
#define RAVER_STATES_H
#include <memory>
#include "SFML/Graphics.hpp"
#include "../Animated.hpp"
#include "../Moving.hpp"
#include <entt/entt.hpp>
#include "../../constants.hpp"
#include "../Raver.hpp"
#include "../../systems/SoundSystem.hpp"
using std::make_unique;
using std::unique_ptr;

//------------------------------------------------------------------------
// Go to the dancefloor and dance
//------------------------------------------------------------------------
struct GoDance
{
    // TODO: Go Dancing with probability
    static void enter(const entt::entity &entity, entt::registry &registry);

    static void execute(const entt::entity &entity, entt::registry &registry);

    static void exit(const entt::entity &entity, entt::registry &registry);
};

//------------------------------------------------------------------------
// Do nothing
//------------------------------------------------------------------------
struct Idle
{
    // TODO: Wandering around
    static void enter(const entt::entity &entity, entt::registry &registry);

    static void execute(const entt::entity &entity, entt::registry &registry);

    static void exit(const entt::entity &entity, entt::registry &registry);
};

//------------------------------------------------------------------------
// Go Drink
// //------------------------------------------------------------------------
struct GoDrink
{
    static void enter(const entt::entity &entity, entt::registry &registry);

    static void execute(const entt::entity &entity, entt::registry &registry);

    static void exit(const entt::entity &entity, entt::registry &registry);
};

#endif