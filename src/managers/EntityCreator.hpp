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
    static EntityCreator &inst();

    void addTextureFromPath(string filePath);

    void createBasicEntity(const string &className, sf::Vector2f position, const string &path, entt::registry &registry);

    sf::Texture &getTextureFromPath(string filePath);

    void createScene(entt::registry &registry);

    void addPlayer(string filePath, entt::registry &registry);
    void addRaver(sf::Vector2f pos, string filePath, entt::registry &registry);

private:
    using TextureResource = std::map<std::string, std::shared_ptr<sf::Texture>>;
    TextureResource textures;

    entt::entity createHuman(sf::Vector2f pos, string filePath, entt::registry &registry);
};
