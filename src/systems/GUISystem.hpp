#pragma once
#include "ISystem.hpp"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backends/SFML.hpp>
#include "../components/Speaker.hpp"
#include "../components/state/RaverStates.hpp"
#include "../managers/EntityCreator.hpp"
#include "../managers/ItemManager.hpp"
#include "Engine.hpp"

class Engine;

class GUISystem : public IDrawSystem
{
public:
    GUISystem(entt::registry &registry, sf::RenderWindow &window, shared_ptr<Engine> engine);
    void draw(entt::registry &registry, sf::RenderWindow &window) override;
    void handleEvent(sf::Event event);

private:
    tgui::Theme theme;
    entt::registry &registry;
    tgui::GuiSFML gui;
    shared_ptr<Engine> engine;

    void loadItemMenu(tgui::GuiBase &gui);
    void loadChatBox(tgui::GuiBase &gui);
    void loadMusicMenu(tgui::GuiBase &gui);

    void speakerUpdate();
    void onGoDanceConstruct(entt::registry &registry, entt::entity entity);
    void onMessage(entt::registry &registry, entt::entity entity);
};
