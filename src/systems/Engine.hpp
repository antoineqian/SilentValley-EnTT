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
#include "GUISystem.hpp"
#include "MovingSystem.hpp"
#include "../managers/EntityCreator.hpp"
#include "../managers/ItemManager.hpp"
#include "../managers/TmxWriter.hpp"
using std::make_unique;

class Engine
{
public:
    void activate()
    {
        updateSystems.emplace_back(make_unique<PlayerControlSystem>());
        updateSystems.emplace_back(make_unique<SoundSystem>(registry));
        updateSystems.emplace_back(make_unique<RaverSystem>(registry));
        updateSystems.emplace_back(make_unique<CollisionSystem>());
        updateSystems.emplace_back(make_unique<MovingSystem>());
        updateSystems.emplace_back(make_unique<AnimationSystem>());

        sf::RenderWindow window{{WINDOW_WIDTH, WINDOW_HEIGHT},
                                "Silent Valley Game"};

        // This allows other processes to run and reduces power consumption
        window.setFramerateLimit(60);
        drawSystems.emplace_back(make_unique<RenderSystem>());
        ItemManager::inst().init();

        EntityCreator::inst().createScene(registry);
        gui = make_unique<GUISystem>(registry, window);

        update(window);
    }

    void update(sf::RenderWindow &window)
    {
        // Game loop
        // Clear the screen
        // Check for user input
        // Calculate the updated graphics
        // Display the updated graphics
        while (window.isOpen())
        {
            // std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << " relative to window\n";
            // std::cout << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << "\n";
            window.clear(sf::Color::Black);
            sf::Event event;

            // If the user pressed "Escape", or clicked on "close", we close the window
            // This will terminate the program
            while (window.pollEvent(event))
            {
                gui->handleEvent(event);
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();

            for (auto &sys : updateSystems)
            {
                sys->update(registry);
            }

            for (auto &sys : drawSystems)
            {
                sys->draw(registry, window);
            }
            gui->draw(registry, window);

            // Calculate the updated graphics
            window.display();
        }
    }

private:
    std::vector<std::unique_ptr<IUpdateSystem>> updateSystems;
    std::vector<std::unique_ptr<IDrawSystem>> drawSystems;
    std::unique_ptr<GUISystem> gui;

    entt::registry registry;
};
