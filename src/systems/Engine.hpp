#include "entt.hpp"
#include "TmxParser.hpp"
#include "../constants.hpp"
#include <SFML/Graphics.hpp>
#include "RenderSystem.hpp"

class Engine
{
public:
    void activate()
    {
    // Create the game's window using an object of class RenderWindow
    // The constructor takes an SFML 2D vector with the window dimensions
    // and an std::string with the window title
    // The SFML code is in the sf namespace
    sf::RenderWindow window{{WINDOW_WIDTH, WINDOW_HEIGHT},
                                 "Silent Valley Game"};

    // Limit the framerate
    // This allows other processes to run and reduces power consumption
    window.setFramerateLimit(60); // Max rate is 60 frames per second

    TmxParser parser;
    parser.loadMap("assets/map/mainMap.tmx", registry, renderSystem);
    update(window);
    }
    
    void update(sf::RenderWindow& window)
    {
    // Game loop
    // Clear the screen
    // Check for user input
    // Calculate the updated graphics
    // Display the updated graphics
    while (window.isOpen())
    {
        // Clear the screen
        window.clear(sf::Color::Black);

        // Check for any events since the last loop iteration
        sf::Event event;

        // If the user pressed "Escape", or clicked on "close", we close the window
        // This will terminate the program
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();


        renderSystem.draw(registry, window);

        // Calculate the updated graphics
        window.display();
    }
    }
    private:
    RenderSystem renderSystem;
    entt::registry registry;
};
