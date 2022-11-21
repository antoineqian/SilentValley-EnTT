#pragma once
#include "pugixml.hpp"
#include <iostream>
#include <string>
#include <SFML/System/Vector2.hpp>

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

    static void test()
    {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file("assets/map/mainMap.tmx");

        std::cout << "Load result: " << result.description() << ", objectgroup name: " << doc.child("map").attribute("tiledversion").value() << std::endl;
        pugi::xml_node objectgroup = doc.child("map").child("objectgroup");
        std::cout << "Last object id: " << objectgroup.last_child().attribute("id").value() << '\n';
        pugi::xml_node object = objectgroup.append_child("object");
        object.append_attribute("id") = "45";
        object.append_attribute("x") = "45";
        object.append_attribute("y") = "45";
        object.append_attribute("width") = "45";
        object.append_attribute("height") = "45";
        doc.save_file("assets/map/mainMap.tmx");
    }

    void addObject(const string &name, sf::Vector2i position);

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
