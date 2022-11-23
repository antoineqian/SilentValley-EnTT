#include "TmxWriter.hpp"

void TmxWriter::addObject(const string &name, sf::Vector2i position, entt::registry &registry)
{
    pugi::xml_node object = objectgroup.append_child("object");

    string sourcePath("objects/" + name + ".png");
    pugi::xpath_variable_set vars;
    vars.add("path", pugi::xpath_type_string);
    vars.set("path", sourcePath.c_str());
    string query = "//image[@source=$path]";

    auto node = objectsDoc.select_node(query.c_str(), &vars).node();
    auto objWidth = node.attribute("width").as_int();
    auto objHeight = node.attribute("height").as_int();

    object.append_attribute("id") = ++lastId;
    object.append_attribute("gid") = objectIdOffset + node.parent().attribute("id").as_uint();
    object.append_attribute("x") = position.x;
    object.append_attribute("y") = position.y;
    object.append_attribute("width") = objWidth;
    object.append_attribute("height") = objHeight;

    try
    {
        // TODO: Fix hardcoded object class
        EntityCreator::inst().createBasicEntity("Object", sf::Vector2f(position.x, position.y), string("assets/map/" + sourcePath), registry);
        map.save_file("assets/map/mainMap.tmx");
        std::cout
            << "Item: " << name << " placed at "
            << position.x << " " << position.y << "\n";
    }
    catch (const char *exception)
    {
        objectsDoc.remove_child(object);
        throw;
    }
}