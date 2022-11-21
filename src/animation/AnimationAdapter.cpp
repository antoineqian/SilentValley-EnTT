
#include "AnimationAdapter.hpp"

unordered_map<string, Animation> AnimationAdapter::getAnimations(sf::Texture &texture)
{
    unordered_map<string, Animation> animations;

    // Idle Animations
    Animation idleAnimationDown;
    idleAnimationDown.setSpriteSheet(texture);
    idleAnimationDown.addFrame(sf::IntRect(288, 32, 16, 32));
    idleAnimationDown.addFrame(sf::IntRect(288 + 16, 32, 16, 32));
    idleAnimationDown.addFrame(sf::IntRect(288 + 32, 32, 16, 32));
    idleAnimationDown.addFrame(sf::IntRect(288 + 48, 32, 16, 32));
    idleAnimationDown.addFrame(sf::IntRect(288 + 64, 32, 16, 32));
    idleAnimationDown.addFrame(sf::IntRect(288 + 80, 32, 16, 32));
    animations.insert({"down_idle", idleAnimationDown});

    Animation idleAnimationLeft;
    idleAnimationLeft.setSpriteSheet(texture);
    idleAnimationLeft.addFrame(sf::IntRect(192, 32, 16, 32));
    idleAnimationLeft.addFrame(sf::IntRect(192 + 16, 32, 16, 32));
    idleAnimationLeft.addFrame(sf::IntRect(192 + 32, 32, 16, 32));
    idleAnimationLeft.addFrame(sf::IntRect(192 + 48, 32, 16, 32));
    idleAnimationLeft.addFrame(sf::IntRect(192 + 64, 32, 16, 32));
    idleAnimationLeft.addFrame(sf::IntRect(192 + 80, 32, 16, 32));
    animations.insert({"left_idle", idleAnimationLeft});

    Animation idleAnimationRight;
    idleAnimationRight.setSpriteSheet(texture);
    idleAnimationRight.addFrame(sf::IntRect(0, 32, 16, 32));
    idleAnimationRight.addFrame(sf::IntRect(0 + 16, 32, 16, 32));
    idleAnimationRight.addFrame(sf::IntRect(0 + 32, 32, 16, 32));
    idleAnimationRight.addFrame(sf::IntRect(0 + 48, 32, 16, 32));
    idleAnimationRight.addFrame(sf::IntRect(0 + 64, 32, 16, 32));
    idleAnimationRight.addFrame(sf::IntRect(0 + 80, 32, 16, 32));
    animations.insert({"right_idle", idleAnimationRight});

    Animation idleAnimationUp;
    idleAnimationUp.setSpriteSheet(texture);
    idleAnimationUp.addFrame(sf::IntRect(96, 32, 16, 32));
    idleAnimationUp.addFrame(sf::IntRect(96 + 16, 32, 16, 32));
    idleAnimationUp.addFrame(sf::IntRect(96 + 32, 32, 16, 32));
    idleAnimationUp.addFrame(sf::IntRect(96 + 48, 32, 16, 32));
    idleAnimationUp.addFrame(sf::IntRect(96 + 64, 32, 16, 32));
    idleAnimationUp.addFrame(sf::IntRect(96 + 80, 32, 16, 32));
    animations.insert({"up_idle", idleAnimationUp});

    // Walking Animations
    Animation walkingAnimationDown;
    walkingAnimationDown.setSpriteSheet(texture);
    walkingAnimationDown.addFrame(sf::IntRect(288, 64, 16, 32));
    walkingAnimationDown.addFrame(sf::IntRect(288 + 16, 64, 16, 32));
    walkingAnimationDown.addFrame(sf::IntRect(288 + 32, 64, 16, 32));
    walkingAnimationDown.addFrame(sf::IntRect(288 + 48, 64, 16, 32));
    walkingAnimationDown.addFrame(sf::IntRect(288 + 64, 64, 16, 32));
    walkingAnimationDown.addFrame(sf::IntRect(288 + 80, 64, 16, 32));
    animations.insert({"down_walking", walkingAnimationDown});

    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(texture);
    walkingAnimationLeft.addFrame(sf::IntRect(192, 64, 16, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(192 + 16, 64, 16, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(192 + 32, 64, 16, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(192 + 48, 64, 16, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(192 + 64, 64, 16, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(192 + 80, 64, 16, 32));
    animations.insert({"left_walking", walkingAnimationLeft});

    Animation walkingAnimationRight;
    walkingAnimationRight.setSpriteSheet(texture);
    walkingAnimationRight.addFrame(sf::IntRect(0, 64, 16, 32));
    walkingAnimationRight.addFrame(sf::IntRect(0 + 16, 64, 16, 32));
    walkingAnimationRight.addFrame(sf::IntRect(0 + 32, 64, 16, 32));
    walkingAnimationRight.addFrame(sf::IntRect(0 + 48, 64, 16, 32));
    walkingAnimationRight.addFrame(sf::IntRect(0 + 64, 64, 16, 32));
    walkingAnimationRight.addFrame(sf::IntRect(0 + 80, 64, 16, 32));
    animations.insert({"right_walking", walkingAnimationRight});

    Animation walkingAnimationUp;
    walkingAnimationUp.setSpriteSheet(texture);
    walkingAnimationUp.addFrame(sf::IntRect(96, 64, 16, 32));
    walkingAnimationUp.addFrame(sf::IntRect(96 + 16, 64, 16, 32));
    walkingAnimationUp.addFrame(sf::IntRect(96 + 32, 64, 16, 32));
    walkingAnimationUp.addFrame(sf::IntRect(96 + 48, 64, 16, 32));
    walkingAnimationUp.addFrame(sf::IntRect(96 + 64, 64, 16, 32));
    walkingAnimationUp.addFrame(sf::IntRect(96 + 80, 64, 16, 32));
    animations.insert({"up_walking", walkingAnimationUp});

    // Dancing Animations

    Animation dancingAnimationRight;
    dancingAnimationRight.setSpriteSheet(texture);
    dancingAnimationRight.addFrame(sf::IntRect(0, 12 * 32, 16, 32));
    dancingAnimationRight.addFrame(sf::IntRect(0 + 16, 12 * 32, 16, 32));
    dancingAnimationRight.addFrame(sf::IntRect(0 + 32, 12 * 32, 16, 32));
    dancingAnimationRight.addFrame(sf::IntRect(0 + 48, 12 * 32, 16, 32));
    dancingAnimationRight.addFrame(sf::IntRect(0 + 64, 12 * 32, 16, 32));
    dancingAnimationRight.addFrame(sf::IntRect(0 + 80, 12 * 32, 16, 32));
    animations.insert({"right_dancing", dancingAnimationRight});

    Animation dancingAnimationUp;
    dancingAnimationUp.setSpriteSheet(texture);
    dancingAnimationUp.addFrame(sf::IntRect(12 * 16, 12 * 32, 16, 32));
    dancingAnimationUp.addFrame(sf::IntRect(12 * 16 + 16, 12 * 32, 16, 32));
    dancingAnimationUp.addFrame(sf::IntRect(12 * 16 + 32, 12 * 32, 16, 32));
    dancingAnimationUp.addFrame(sf::IntRect(12 * 16 + 48, 12 * 32, 16, 32));
    dancingAnimationUp.addFrame(sf::IntRect(12 * 16 + 64, 12 * 32, 16, 32));
    dancingAnimationUp.addFrame(sf::IntRect(12 * 16 + 80, 12 * 32, 16, 32));
    animations.insert({"up_dancing", dancingAnimationUp});

    Animation dancingAnimationLeft;
    dancingAnimationLeft.setSpriteSheet(texture);
    dancingAnimationLeft.addFrame(sf::IntRect(2 * 12 * 16, 12 * 32, 16, 32));
    dancingAnimationLeft.addFrame(sf::IntRect(2 * 12 * 16 + 16, 12 * 32, 16, 32));
    dancingAnimationLeft.addFrame(sf::IntRect(2 * 12 * 16 + 32, 12 * 32, 16, 32));
    dancingAnimationLeft.addFrame(sf::IntRect(2 * 12 * 16 + 48, 12 * 32, 16, 32));
    dancingAnimationLeft.addFrame(sf::IntRect(2 * 12 * 16 + 64, 12 * 32, 16, 32));
    dancingAnimationLeft.addFrame(sf::IntRect(2 * 12 * 16 + 80, 12 * 32, 16, 32));
    animations.insert({"left_dancing", dancingAnimationLeft});

    Animation dancingAnimationDown;
    dancingAnimationDown.setSpriteSheet(texture);
    dancingAnimationDown.addFrame(sf::IntRect(3 * 12 * 16, 12 * 32, 16, 32));
    dancingAnimationDown.addFrame(sf::IntRect(3 * 12 * 16 + 16, 12 * 32, 16, 32));
    dancingAnimationDown.addFrame(sf::IntRect(3 * 12 * 16 + 32, 12 * 32, 16, 32));
    dancingAnimationDown.addFrame(sf::IntRect(3 * 12 * 16 + 48, 12 * 32, 16, 32));
    dancingAnimationDown.addFrame(sf::IntRect(3 * 12 * 16 + 64, 12 * 32, 16, 32));
    dancingAnimationDown.addFrame(sf::IntRect(3 * 12 * 16 + 80, 12 * 32, 16, 32));
    animations.insert({"down_dancing", dancingAnimationDown});

    return animations;
}
