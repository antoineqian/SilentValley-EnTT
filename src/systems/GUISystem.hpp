#pragma once
#include "ISystem.hpp"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backends/SFML.hpp>
#include "../components/Speaker.hpp"
#include <sstream>
using std::ostringstream;
class GUISystem : public IDrawSystem
{
public:
    GUISystem(entt::registry &registry, sf::RenderWindow &window);
    void draw(entt::registry &registry, sf::RenderWindow &window) override;

private:
    entt::registry &registry;
    tgui::GuiSFML gui;

    void speakerUpdate();
};
