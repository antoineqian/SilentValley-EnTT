#pragma once
#include "../animation/AnimatedSprite.hpp"
#include "../animation/Animation.hpp"
#include <unordered_map>
#include <string>
struct Animated
{
    Animated(AnimatedSprite animatedSprite, std::unordered_map<std::string, Animation> animations, Animation currentAnimation)
        : animatedSprite(animatedSprite), animations(animations), currentAnimation(currentAnimation){};
    AnimatedSprite animatedSprite;
    std::unordered_map<std::string, Animation> animations;
    Animation currentAnimation;
};