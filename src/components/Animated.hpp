#pragma once
#include "../animation/AnimatedSprite.hpp"
#include "../animation/Animation.hpp"
#include "Collision.hpp"
#include "../constants.hpp"
#include <unordered_map>
#include <string>
struct Animated : public Collision
{
    Animated(AnimatedSprite animatedSprite, std::unordered_map<std::string, Animation> animations, Animation currentAnimation)
        : animatedSprite(animatedSprite), animations(animations), currentAnimation(currentAnimation){};
    AnimatedSprite animatedSprite;
    std::unordered_map<std::string, Animation> animations;
    Animation currentAnimation;

    virtual sf::FloatRect getBoundingBox() const override;
    virtual sf::FloatRect getHitBox() const override;
    operator AnimatedSprite &() { return animatedSprite; }
};