#pragma once
#include "ISystem.hpp"
#include "../managers/TmxWriter.hpp"
#include "../components/Message.hpp"
#include "../managers/DataBase.hpp"
#include <sstream>
using std::ostringstream;

class BuilderSystem : public IUpdateSystem
{
public:
    void update(entt::registry &registry, sf::RenderWindow &window) override;
    void setItem(shared_ptr<const Item> item);

private:
    bool isItemSelected = false;
    std::weak_ptr<const Item> selectedItem;
    void placeItem(shared_ptr<const Item> item, sf::Vector2i mousePos, entt::registry &registry);
};