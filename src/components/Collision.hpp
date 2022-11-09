#pragma once
#include <SFML/Graphics.hpp>

struct Collision
{
    virtual sf::FloatRect getBoundingBox() const = 0;
    virtual sf::FloatRect getHitBox() const = 0;
    virtual ~Collision() {}
    // return {box.left + box.width * 0.1f, box.top + box.height * 0.7f, box.width * 0.8f, box.height * 0.3f};
};