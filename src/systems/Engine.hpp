#pragma once
#include "entt.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include "ISystem.hpp"
#include "RenderSystem.hpp"
#include "PlayerControlSystem.hpp"
#include "RaverSystem.hpp"
#include "AnimationSystem.hpp"
#include "CollisionSystem.hpp"
#include "SoundSystem.hpp"
#include "BuilderSystem.hpp"
#include "GUISystem.hpp"
#include "MovingSystem.hpp"
#include "../managers/EntityCreator.hpp"
#include "../managers/DataBase.hpp"
#include "../managers/TmxWriter.hpp"
using std::make_shared;
using std::make_unique;

// class Controller;
class GUISystem;

class Engine : public std::enable_shared_from_this<Engine>
{
public:
    void activate();

    void update(sf::RenderWindow &window);

    template <typename System>
    shared_ptr<IUpdateSystem> get();

    void onSongSelect(size_t index, const string &songName);
    void onItemSelect(shared_ptr<const Item> item);
    std::shared_ptr<Engine> getptr();

    [[nodiscard]] static std::shared_ptr<Engine> create()
    {
        // Not using std::make_shared<Engine> because the c'tor is private.
        return std::shared_ptr<Engine>(new Engine());
    }

private:
    Engine() = default;
    std::vector<std::shared_ptr<IUpdateSystem>> updateSystems;
    std::vector<std::unique_ptr<IDrawSystem>> drawSystems;
    std::unique_ptr<GUISystem> gui;
    entt::registry registry;
};
