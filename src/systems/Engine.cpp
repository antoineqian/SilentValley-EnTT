#include "Engine.hpp"

void Engine::activate()
{
    updateSystems.emplace_back(make_shared<PlayerControlSystem>());
    updateSystems.emplace_back(make_shared<SoundSystem>(registry));
    updateSystems.emplace_back(make_shared<MovingSystem>());        // Moving/SoundSystem after PlayerControlSystem to account for player input
    updateSystems.emplace_back(make_shared<RaverSystem>(registry)); // RaverSystem after MovingSystem to override with state-specific animations
    updateSystems.emplace_back(make_shared<CollisionSystem>());     // CollisionSystem after MovingSystem to update Collision
    updateSystems.emplace_back(make_shared<AnimationSystem>());     // AnimationSystem after Raver/Moving system to play according animation
    updateSystems.emplace_back(make_shared<BuilderSystem>());

    sf::RenderWindow window{{WINDOW_WIDTH, WINDOW_HEIGHT},
                            "Silent Valley Game"};

    // This allows other processes to run and reduces power consumption
    window.setFramerateLimit(60);
    drawSystems.emplace_back(make_unique<RenderSystem>());
    ItemManager::inst().init();
    EntityCreator::inst().createScene(registry);

    gui = make_unique<GUISystem>(registry, window, getptr());

    update(window);
}

void Engine::update(sf::RenderWindow &window)
{
    // Game loop
    // Clear the screen
    // Check for user input
    // Calculate the updated graphics
    // Display the updated graphics
    while (window.isOpen())
    {
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
            sys->update(registry, window);
        }

        for (auto &sys : drawSystems)
        {
            sys->draw(registry, window);
        }
        gui->draw(registry, window);
        window.display();
    }
}

template <typename System>
shared_ptr<IUpdateSystem> Engine::get()
{
    for (auto p : updateSystems)
    {
        shared_ptr<System> result;
        if ((result = dynamic_pointer_cast<System>(p)))
            return result;
    }
    throw "Unknown System type";
}

std::shared_ptr<Engine> Engine::getptr()
{
    return shared_from_this();
}

void Engine::onSongSelect(const string &songName)
{
    auto soundSystem = dynamic_pointer_cast<SoundSystem>(get<SoundSystem>());
    soundSystem->select(songName);
}

void Engine::onItemSelect(shared_ptr<const Item> item)
{
    auto builderSystem = dynamic_pointer_cast<BuilderSystem>(get<BuilderSystem>());
    builderSystem->setItem(item);
    std::cout << item->getName() << " selected\n";
}
