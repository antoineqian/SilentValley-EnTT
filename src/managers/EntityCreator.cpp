#include "EntityCreator.hpp"

EntityCreator &EntityCreator::inst()
{
    static EntityCreator mgr;
    return mgr;
}

void EntityCreator::addTextureFromPath(string filePath)
{
    std::unique_ptr<sf::Texture> newTexture = std::make_unique<sf::Texture>();
    newTexture->loadFromFile(filePath);
    textures.insert(std::make_pair(filePath, std::move(newTexture)));
}

void EntityCreator::createBasicEntity(const string &className, sf::Vector2f position, const string &path, entt::registry &registry)
{

    auto entity = registry.create();
    auto &sprite = registry.emplace<sf::Sprite>(entity, sf::Sprite());
    addTextureFromPath(path);
    sprite.setTexture(getTextureFromPath(path));
    sprite.setPosition(position.x, position.y);
    registry.view<Collision>().each(
        [&registry, &sprite, &entity](auto &collision)
        {
            auto &box = collision.hitBox;
            if (box.intersects(shrinkToHitBox(sprite.getGlobalBounds())))
            {
                registry.destroy(entity);
                throw "Cannot place entity on top of another entity";
            }
        });
    registry.emplace<Collision>(entity, shrinkToHitBox(sprite.getGlobalBounds()));

    if (className == string("Speaker"))
    {
        registry.emplace<Speaker>(entity);
    }
};

sf::Texture &EntityCreator::getTextureFromPath(string filePath)
{
    return *(textures[filePath]);
}

void EntityCreator::createScene(entt::registry &registry)
{
    TmxParser::loadMap("assets/map/mainMap.tmx", registry);
    addPlayer("assets/complete_player.png", registry);
    addRaver(sf::Vector2f(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3), "assets/characters/Premade_Character_07.png", registry);
    // addRaver(sf::Vector2f(WINDOW_WIDTH / 3, 2 * WINDOW_HEIGHT / 3), "assets/characters/Premade_Character_07.png");
}

void EntityCreator::addPlayer(string filePath, entt::registry &registry)
{
    auto entity = createHuman(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), filePath, registry);
    registry.emplace<PlayerController>(entity);
}

entt::entity EntityCreator::createHuman(sf::Vector2f pos, string filePath, entt::registry &registry)
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

void EntityCreator::addRaver(sf::Vector2f pos, string filePath, entt::registry &registry)
{
    auto entity = createHuman(pos, filePath, registry);
    auto &raver = registry.emplace<Raver>(entity);
    raver.thirst = 1.f;
    raver.name = "Samantha";
    registry.emplace<Idle>(entity);
}
