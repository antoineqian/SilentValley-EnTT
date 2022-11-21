#pragma once
#include "pugixml.hpp"
#include <iostream>
#include <string>
#include <SFML/System/Vector2.hpp>
#include "EntityCreator.hpp"
using std::string;

class TmxWriter
{
public:
    static TmxWriter &inst()
    {
        static TmxWriter mgr;
        return mgr;
    }

    void init()
    {
    }

    void addObject(const string &name, sf::Vector2i position, entt::registry &registry);

private:
    TmxWriter()
    {
        map.load_file("assets/map/mainMap.tmx");
        objectgroup = TmxWriter::map.child("map").child("objectgroup");
        lastId = objectgroup.last_child().attribute("id").as_uint();
        objectIdOffset = map.child("map").find_child_by_attribute("tileset", "source", "Objects.tsx").attribute("firstgid").as_int();
        std::cout << "Offset " << objectIdOffset << '\n';
        objectsDoc.load_file("assets/map/Objects.tsx");
        objectsDoc.child("tileset").child("tile");
    }

    int objectIdOffset;
    pugi::xml_document map;
    pugi::xml_node objectgroup;
    pugi::xml_document objectsDoc;
    pugi::xml_node all_objects;
    int lastId;
};
