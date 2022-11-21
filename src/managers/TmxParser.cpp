#include "TmxParser.hpp"

void TmxParser::loadMap(string filepath, entt::registry &registry)
{
    tmx::Map gameMap;
    gameMap.load(filepath);
    const auto &tileSets = gameMap.getTilesets();
    unique_ptr<const tmx::Tileset> objectTileSet = nullptr;

    for (auto &ts : tileSets)
    {
        if (ts.getName() == string("Objects"))
        {
            objectTileSet = std::make_unique<const tmx::Tileset>(ts);
        }
    }

    for (std::size_t i = 0; i < gameMap.getLayers().size(); i++)
    {
        if (gameMap.getLayers()[i]->getType() == tmx::Layer::Type::Tile)
        {
            auto entity = registry.create();
            MapLayer layer(gameMap, i);
            registry.emplace<MapLayer>(entity, gameMap, i);
        }
        if (gameMap.getLayers()[i]->getType() == tmx::Layer::Type::Object)
        {
            const auto &objectLayer = gameMap.getLayers()[i]->getLayerAs<tmx::ObjectGroup>();
            for (const auto &object : objectLayer.getObjects())
            {
                const auto pos = object.getPosition();
                auto tID = object.getTileID();
                EntityCreator::inst().createBasicEntity(object.getClass(), sf::Vector2f(pos.x, pos.y), objectTileSet->getTile(tID)->imagePath, registry);
            }
        }
    }
}
