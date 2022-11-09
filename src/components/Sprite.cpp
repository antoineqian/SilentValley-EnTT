#include "Sprite.hpp"

sf::FloatRect Sprite::getBoundingBox() const
{
    return sprite.getGlobalBounds();
}

sf::FloatRect Sprite::getHitBox() const
{
    auto box = getBoundingBox();
    return {box.left + box.width * 0.1f, box.top + box.height * 0.7f, box.width * 0.8f, box.height * 0.3f};
}