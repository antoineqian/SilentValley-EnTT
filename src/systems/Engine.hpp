#include "entt.hpp"
#include "TmxParser.hpp"
#include "../constants.hpp"
#include <SFML/Graphics.hpp>
#include "RenderSystem.hpp"
#include "../components/Moving.hpp"
#include "../components/PlayerController.hpp"
#include "../components/Collision.hpp"
#include "ISystem.hpp"
#include "PlayerControlSystem.hpp"
#include "AnimationSystem.hpp"
#include "CollisionSystem.hpp"
#include "SoundSystem.hpp"
#include "MovingSystem.hpp"
#include <memory>
#include "../animation/AnimationAdapter.hpp"
using std::make_unique;

class Engine
{
public:
    void activate()
    {
        updateSystems.emplace_back(make_unique<PlayerControlSystem>());
        updateSystems.emplace_back(make_unique<CollisionSystem>());
        updateSystems.emplace_back(make_unique<MovingSystem>());
        updateSystems.emplace_back(make_unique<AnimationSystem>());
        updateSystems.emplace_back(make_unique<SoundSystem>(registry));

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

        addPlayer("assets/complete_player.png");

        update(window);
    }

    void addPlayer(string filePath)
    {
        auto entity = registry.create();

        renderSystem.addTextureFromPath(filePath);
        auto &texture = renderSystem.getTextureFromPath(filePath);

        AnimatedSprite animatedSprite(sf::seconds(0.2), true, true);
        const auto &animations = AnimationAdapter::getAnimations(texture);
        auto currentAnimation = animations.at("down_walking");
        animatedSprite.setAnimation(currentAnimation);
        animatedSprite.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
        Animated animatedComponent(animatedSprite, animations, currentAnimation);
        registry.emplace<Animated>(entity, animatedComponent);
        registry.emplace<PlayerController>(entity);
        registry.emplace<Moving>(entity, sf::Vector2f(0.f, 0.f));
        registry.emplace<Collision>(entity, shrinkToHitBox(animatedSprite.getGlobalBounds()));
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

            for (auto &sys : updateSystems)
            {
                sys->update(registry);
            }

            renderSystem.draw(registry, window);

            // Calculate the updated graphics
            window.display();
        }
    }

private:
    RenderSystem renderSystem;
    std::vector<std::unique_ptr<IUpdateSystem>> updateSystems;

    entt::registry registry;
};
