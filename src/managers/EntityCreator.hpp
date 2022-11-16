#pragma once
#include "../animation/AnimationAdapter.hpp"
#include "TmxParser.hpp"
#include "../constants.hpp"
#include "../components/Moving.hpp"
#include "../components/Animated.hpp"
#include "../components/state/RaverStates.hpp"
#include "../components/PlayerController.hpp"
#include "../components/Collision.hpp"
#include "../components/Raver.hpp"

class TmxParser;

// Singleton class
class EntityCreator
{
public:
    static EntityCreator &inst(entt::registry &registry);

    void addTextureFromPath(string filePath);

    sf::Texture &getTextureFromPath(string filePath);

    void createScene();

    void addPlayer(string filePath);
    void addRaver(sf::Vector2f pos, string filePath);

private:
    EntityCreator(entt::registry &registry);

    entt::registry &registry;
    using TextureResource = std::map<std::string, std::shared_ptr<sf::Texture>>;
    TextureResource textures;

    entt::entity createHuman(sf::Vector2f pos, string filePath);
};
