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
    bool inState{true};

    static void enter(entt::entity entity, entt::registry &registry);

    static void execute(entt::entity entity, entt::registry &registry);

    static void exit(entt::entity entity, entt::registry &registry);
};

struct Idle
{
    bool inState{true};
    // public:

    static void enter(entt::entity entity, entt::registry &registry);

    static void execute(entt::entity entity, entt::registry &registry);

    static void exit(entt::entity entity, entt::registry &registry);
};

#endif