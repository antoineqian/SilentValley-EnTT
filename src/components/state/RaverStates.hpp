#ifndef RAVER_STATES_H
#define RAVER_STATES_H
#include <memory>
#include "SFML/Graphics.hpp"
#include "../Animated.hpp"
#include "../Moving.hpp"
#include "entt.hpp"
#include "../../constants.hpp"
#include "../Raver.hpp"
using std::make_unique;
using std::unique_ptr;

//------------------------------------------------------------------------
// Go to the dancefloor and dance
//------------------------------------------------------------------------
struct GoDance
{
    static void enter(entt::entity &entity, entt::registry &registry);

    static void execute(entt::entity &entity, entt::registry &registry);

    static void exit(entt::entity &entity, entt::registry &registry);
};

//------------------------------------------------------------------------
// Do nothing
//------------------------------------------------------------------------
struct Idle
{
    static void enter(entt::entity &entity, entt::registry &registry);

    static void execute(entt::entity &entity, entt::registry &registry);

    static void exit(entt::entity &entity, entt::registry &registry);
};

#endif