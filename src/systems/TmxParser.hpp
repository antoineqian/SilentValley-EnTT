#include <tmxlite/Map.hpp>
#include "../../external/Layer.hpp"
#include <memory>
#include <string>
using std::string;
using std::unique_ptr;

class TmxParser
{
public:
    void loadMap(string filepath, entt::registry& registry)
    {
        tmx::Map gameMap;
        gameMap.load(filepath);
        const auto &tileSets = gameMap.getTilesets();
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
            // if (gameMap.getLayers()[i]->getType() == tmx::Layer::Type::Object)
            // {
            //     const auto &objectLayer = gameMap.getLayers()[i]->getLayerAs<tmx::ObjectGroup>();
            //     for (const auto &object : objectLayer.getObjects())
            //     {

            //         // auto tID = object.getTileID();
            //         // auto path = objectTileSet->getTile(tID)->imagePath;
            //         // enttMgr.addTextureFromPath(path);
            //         // sf::Sprite sprite;
            //         // sprite.setTexture(getTextureFromPath(path));
            //         // sprite.setPosition(pos.x, pos.y);

            //         // auto entity = registry.create();
            //         // if (object.getClass() == string('Speaker'))
            //         // {
            //         //     enttMgr.registry.emplace<Speaker>(entity, 1, sprite, object.getName());
            //         // }
            //         // else
            //         // {
            //         //     enttMgr.registry.emplace<StaticEntity>(entity, 1, sprite, object.getName());
            //         // }
            //     }
            // }
            // for (auto &&layer : mapLayers)
            // {
            //     window.draw(*layer);
            // }
        }
    }

private:
    // void addObjectAsEntity(const tmx::Object &object)
    // {
    //     const auto pos = object.getPosition();
    //     auto tID = object.getTileID();
    //     auto path = objectTileSet->getTile(tID)->imagePath;
    //     addTextureFromPath(path);
    //     sf::Sprite sprite;
    //     sprite.setTexture(getTextureFromPath(path));
    //     sprite.setPosition(pos.x, pos.y);

    //     // TODO: Templatize ?
    //     if (object.getClass() == string("Speaker"))
    //     {
    //         auto ptr = make_shared<Speaker>(1, sprite, object.getName());
    //         // auto ptr_alias = ptr.get();

    //         // Get the hash code for the entity object's type
    //         auto hash = typeid(Speaker).hash_code();
    //         // Insert the alias pointer into the map
    //         groupedEntities[hash].emplace_back(ptr);
    //         // allEntities.push_back(std::move(ptr));
    //         allEntities.push_back(ptr);
    //     }
    //     else
    //     {
    //         auto ptr = make_shared<StaticEntity>(1, sprite, object.getName());
    //         // auto ptr_alias = ptr.get();
    //         // Get the hash code for the entity object's type
    //         auto hash = typeid(StaticEntity).hash_code();
    //         // Insert the alias pointer into the map
    //         groupedEntities[hash].emplace_back(ptr);
    //         // allEntities.push_back(std::move(ptr));
    //         allEntities.push_back(ptr);
    //     }
    // }

    unique_ptr<const tmx::Tileset> objectTileSet = nullptr;
};
