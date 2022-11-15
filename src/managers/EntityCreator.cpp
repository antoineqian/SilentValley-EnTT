#include "EntityCreator.hpp"

EntityCreator::EntityCreator(entt::registry &registry) : registry(registry)
{
    TmxParser::loadMap("assets/map/mainMap.tmx", registry, *this);
}

void EntityCreator::addTextureFromPath(string filePath)
{
    std::unique_ptr<sf::Texture> newTexture = std::make_unique<sf::Texture>();
    newTexture->loadFromFile(filePath);
    textures.insert(std::make_pair(filePath, std::move(newTexture)));
}

sf::Texture &EntityCreator::getTextureFromPath(string filePath)
{
    return *(textures[filePath]);
}

void EntityCreator::createScene()
{
    addPlayer("assets/complete_player.png");
    addRaver(sf::Vector2f(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3), "assets/characters/Premade_Character_07.png");
    // addRaver(sf::Vector2f(WINDOW_WIDTH / 3, 2 * WINDOW_HEIGHT / 3), "assets/characters/Premade_Character_07.png");
}

void EntityCreator::addPlayer(string filePath)
{
    auto entity = createHuman(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), filePath);
    registry.emplace<PlayerController>(entity);
}

entt::entity EntityCreator::createHuman(sf::Vector2f pos, string filePath)
{
    auto entity = registry.create();
    addTextureFromPath(filePath);
    auto &texture = getTextureFromPath(filePath);

    AnimatedSprite animatedSprite(sf::seconds(0.2), true, true);
    const auto &animations = AnimationAdapter::getAnimations(texture);
    auto currentAnimation = animations.at("down_walking");
    animatedSprite.setAnimation(currentAnimation);
    animatedSprite.setPosition(pos);
    Animated animatedComponent(animatedSprite, animations, currentAnimation);
    registry.emplace<Animated>(entity, animatedComponent);
    registry.emplace<Moving>(entity, sf::Vector2f(0.f, 0.f));
    registry.emplace<Collision>(entity, shrinkToHitBox(animatedSprite.getGlobalBounds()));
    return entity;
}

void EntityCreator::addRaver(sf::Vector2f pos, string filePath)
{
    auto entity = createHuman(pos, filePath);
    auto &raver = registry.emplace<Raver>(entity);
    raver.thirst = 1.f;
    registry.emplace<Idle>(entity);
}
