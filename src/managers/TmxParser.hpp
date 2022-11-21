#pragma once
#include "entt.hpp"
#include <tmxlite/Map.hpp>
#include "../../external/Layer.hpp"
#include "../components/Collision.hpp"
#include "../components/Speaker.hpp"
#include "../constants.hpp"
#include <SFML/Graphics.hpp>
#include "EntityCreator.hpp"
#include <memory>
#include <string>
using std::string;
using std::unique_ptr;

class EntityCreator;

class TmxParser
{
public:
    static void loadMap(string filepath, entt::registry &registry, EntityCreator &creator);

    // private:
    //     unique_ptr<const tmx::Tileset> objectTileSet = nullptr;
};
