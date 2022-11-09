#include "Animated.hpp"

sf::FloatRect Animated::getBoundingBox() const
{
    auto box = animatedSprite.getGlobalBounds();
    // std::cout << "Left :" << box.left << " / Top : " << box.top + 12 << '\n';
    return {box.left, box.top + 12, TILE_SIZE, PLAYER_HEIGHT};
}

sf::FloatRect Animated::getHitBox() const
{
    auto box = getBoundingBox();
    // std::cout << "Left :" << box.left << " / Top : " << box.top + 12 << '\n';
    return {box.left + box.width * 0.1f, box.top + box.height * 0.7f, box.width * 0.8f, box.height * 0.3f};
    // return box;
}