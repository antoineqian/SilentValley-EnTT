#pragma once
#include "ISystem.hpp"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backends/SFML.hpp>
#include "../components/Speaker.hpp"
#include "../components/state/RaverStates.hpp"
#include "../managers/EntityCreator.hpp"
#include "../managers/ItemManager.hpp"
#include <sstream>
using std::ostringstream;
class GUISystem : public IDrawSystem
{
public:
    GUISystem(entt::registry &registry, sf::RenderWindow &window);
    void draw(entt::registry &registry, sf::RenderWindow &window) override;
    void handleEvent(sf::Event event);
    void selectItem(string name);

private:
    entt::registry &registry;
    tgui::GuiSFML gui;
    void loadMenu(tgui::GuiBase &gui);
    void speakerUpdate();
    void onGoDanceConstruct(entt::registry &registry, entt::entity entity);
    bool itemSelected;
    void placeItem();
};
