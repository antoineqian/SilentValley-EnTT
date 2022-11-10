#pragma once
#include <map>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <entt.hpp>
#include "../../external/Layer.hpp"
#include "../components/Moving.hpp"
#include "../components/Collision.hpp"
#include "../components/Animated.hpp"
using std::string;

class RenderSystem
{
public:
    void addTextureFromPath(string filePath);
    sf::Texture &getTextureFromPath(string filePath);
    void draw(entt::registry &registry, sf::RenderWindow &window);

private:
    using TextureResource = std::map<std::string, std::shared_ptr<sf::Texture>>;
    TextureResource textures;
};