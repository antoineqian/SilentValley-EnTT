#include <tmxlite/Map.hpp>
#include "../../external/Layer.hpp"
#include <SFML/Graphics.hpp>
#include "RenderSystem.hpp"
#include <memory>
#include <string>
using std::string;
using std::unique_ptr;

class TmxParser
{
public:
    void loadMap(string filepath, entt::registry& registry, RenderSystem &renderSystem)
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
            if (gameMap.getLayers()[i]->getType() == tmx::Layer::Type::Object)
            {
                const auto &objectLayer = gameMap.getLayers()[i]->getLayerAs<tmx::ObjectGroup>();
                for (const auto &object : objectLayer.getObjects())
                {
                    auto entity = registry.create();
                    
                    const auto pos = object.getPosition();
                    auto tID = object.getTileID();
                    auto path = objectTileSet->getTile(tID)->imagePath;
                    renderSystem.addTextureFromPath(path);
                    auto &sprite = registry.emplace<sf::Sprite>(entity, sf::Sprite());

                    sprite.setTexture(renderSystem.getTextureFromPath(path));
                    sprite.setPosition(pos.x, pos.y);

            //         // auto entity = registry.create();
            //         // if (object.getClass() == string('Speaker'))
            //         // {
            //         //     enttMgr.registry.emplace<Speaker>(entity, 1, sprite, object.getName());
            //         // }
            //         // else
            //         // {
            //         //     enttMgr.registry.emplace<StaticEntity>(entity, 1, sprite, object.getName());
            //         // }
                }
            }
        }
    }

private:
    unique_ptr<const tmx::Tileset> objectTileSet = nullptr;
};
