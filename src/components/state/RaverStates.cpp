#include "RaverStates.hpp"
#include <random>

bool targetReached(sf::Vector2f target, sf::Vector2f position)
{
    auto diff = target - position;
    return (abs(diff.x) <= 16 && abs(diff.y) <= 16);
}

sf::Vector2f seekTarget(sf::Vector2f target, sf::Vector2f position)
{
    sf::Vector2f velocity;
    if (targetReached(target, position))
    {
        velocity.x = 0;
        velocity.y = 0;
        return velocity;
    }
    // TODO: checkObstacles();

    auto diff = target - position;
    if (abs(diff.x) > 16 && abs(diff.y) > 16)
    {
        if (abs(diff.x) > 2 * abs(diff.y))
        {
            velocity.x = (diff.x > 0 ? 1 : -1) * PLAYER_SPEED;
            velocity.y = 0;
        }
        else
        {
            velocity.y = (diff.y > 0 ? 1 : -1) * PLAYER_SPEED;
            velocity.x = 0;
        }
    }
    else if (abs(diff.x) > 16)
    {
        velocity.x = (diff.x > 0 ? 1 : -1) * PLAYER_SPEED;
        velocity.y = 0;
    }
    else if (abs(diff.y) > 16)
    {
        velocity.y = (diff.y > 0 ? 1 : -1) * PLAYER_SPEED;
        velocity.x = 0;
    }
    return velocity;
}

void GoDance::enter(entt::entity entity, entt::registry &registry)
{
    std::random_device rd;                          // obtain a random number from hardware
    std::mt19937 gen(rd());                         // seed the generator
    std::uniform_int_distribution<> distr(-96, 96); // define the range
    auto raver = registry.get<Raver>(entity);

    raver.target = sf::Vector2f(WINDOW_WIDTH / 2.f + distr(gen),
                                WINDOW_HEIGHT / 2.f + distr(gen));
}

void GoDance::execute(entt::entity entity, entt::registry &registry)
{
    auto [raver, mov, anim] = registry.get<Raver, Moving, Animated>(entity);
    auto target = raver.target;
    auto pos = anim.animatedSprite.getPosition();
    mov.velocity = seekTarget(target, pos);
    if (targetReached(target, pos))
    {
        anim.currentAnimation = anim.animations["up_walking"];
    }
}

void GoDance::exit(entt::entity entity, entt::registry &registry)
{
    auto anim = registry.get<Animated>(entity);
    anim.currentAnimation = anim.animations["up_dancing"];
}

void Idle::enter(entt::entity entity, entt::registry &registry)
{
}

void Idle::execute(entt::entity entity, entt::registry &registry)
{
}

void Idle::exit(entt::entity entity, entt::registry &registry)
{
}
