#include "RenderSystem.hpp"

void RenderSystem::addTextureFromPath(string filePath)
{
    std::unique_ptr<sf::Texture> newTexture = std::make_unique<sf::Texture>();
    newTexture->loadFromFile(filePath);
    textures.insert(std::make_pair(filePath, std::move(newTexture)));
}

sf::Texture &RenderSystem::getTextureFromPath(string filePath)
{
    return *(textures[filePath]);
}

void RenderSystem::draw(entt::registry& registry, sf::RenderWindow& window){
    
    registry.view<MapLayer>().each([&](auto& layer)
	{
	   window.draw(layer);
    });
};
