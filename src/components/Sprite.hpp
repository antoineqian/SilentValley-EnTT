#pragma once
#include "Collision.hpp"
#include <SFML/Graphics.hpp>

struct Sprite : Collision {
    Sprite(sf::Sprite sprite) :sprite(sprite) {}
    sf::Sprite sprite;
    virtual sf::FloatRect getBoundingBox() const override;
    virtual sf::FloatRect getHitBox() const override;
    operator sf::Sprite& () {return sprite;}
};
