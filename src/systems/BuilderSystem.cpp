#include "BuilderSystem.hpp"

void BuilderSystem::setItem(shared_ptr<const Item> item)
{
    isItemSelected = true;
    selectedItem = item;
}

void BuilderSystem::update(entt::registry &registry, sf::RenderWindow &window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isItemSelected)
    {
        std::cout << "Left click in update\n";

        auto mousePos = sf::Mouse::getPosition(window);
        if (mousePos.x < 0 || mousePos.x > WINDOW_WIDTH || mousePos.y < 0 || mousePos.y > WINDOW_HEIGHT)
            return;
        auto ptr = selectedItem.lock();
        placeItem(ptr, mousePos, registry);
    }
}

void BuilderSystem::placeItem(shared_ptr<const Item> item, sf::Vector2i mousePos, entt::registry &registry)
{
    std::cout << "Placing \n";

    // TODO: Bug with the position when the window is moved
    // TODO: Verify that you don't click on the menu;
    string message;
    try
    {
        TmxWriter::inst().addObject(item->getName(), mousePos, registry);
        isItemSelected = false;
        ostringstream oss;
        oss << item->getName() << " added!";
        message = oss.str();
    }
    catch (const char *exception)
    {
        message = exception;
    }
    auto entity = registry.create();
    registry.emplace<Message>(entity, message);
    registry.destroy(entity);
}