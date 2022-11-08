#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include <string>
// #include "animation/Animation.hpp"
// #include "animation/AnimationAdapter.hpp"
using std::make_shared;
// #include "entt.hpp"

// The main function for the program

// struct position
// {
//     float x;
//     float y;
// };

// struct velocity
// {
//     float dx;
//     float dy;
// };

// struct sprite
// {
//     sf::Sprite sprite;
// };

// struct animated
// {
//     unordered_map<string, Animation> animations;
//     Animation currentAnimation;
//     sf::Clock frameClock;
// };

int main()
{
    // Create the game's window using an object of class RenderWindow
    // The constructor takes an SFML 2D vector with the window dimensions
    // and an std::string with the window title
    // The SFML code is in the sf namespace
    sf::RenderWindow game_window{{WINDOW_WIDTH, WINDOW_HEIGHT},
                                 "Silent Valley Game"};

    // Limit the framerate
    // This allows other processes to run and reduces power consumption
    game_window.setFramerateLimit(60); // Max rate is 60 frames per second

    // entt::registry registry;

    // auto filePath = "assets/complete_player_modernStyle.png";
    // std::unique_ptr<sf::Texture> newTexture = std::make_unique<sf::Texture>();
    // newTexture->loadFromFile(filePath);

    // auto player = registry.create();
    // registry.emplace<position>(player, constants::window_width / 2.f,
    //                            constants::window_height / 2.f);
    // registry.emplace<velocity>(player, 0.f, 0.f);

    // auto animations = AnimationAdapter::getAnimations(*newTexture);
    // // Set the initial position
    // AnimatedSprite animatedSprite;
    // animatedSprite.setPosition(0.f, 0.f);
    // auto currentAnimation = animations["down_walking"];
    // animatedSprite.setAnimation(currentAnimation);
    // registry.emplace<animated>(player, animatedSprite);

    // Game loop
    // Clear the screen
    // Check for user input
    // Calculate the updated graphics
    // Display the updated graphics
    while (game_window.isOpen())
    {
        // Clear the screen
        game_window.clear(sf::Color::Black);

        // Check for any events since the last loop iteration
        sf::Event event;

        // If the user pressed "Escape", or clicked on "close", we close the window
        // This will terminate the program
        while (game_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                game_window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            game_window.close();

        // Calculate the updated graphics
        game_window.display();
    }
}
