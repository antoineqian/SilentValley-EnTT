#include "GUISystem.hpp"

void GUISystem::handleEvent(sf::Event event)
{
    gui.handleEvent(event);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isItemSelected)
    {
        auto ptr = selectedItem.lock();
        placeItem(ptr, sf::Mouse::getPosition(window));
    }
}

void GUISystem::placeItem(shared_ptr<const Item> item, sf::Vector2i mousePos)
{
    // TODO: Verify that you don't click on the menu;
    TmxWriter::inst().addObject(item->getName(), mousePos);
    isItemSelected = false;
}

void loadChatBox(tgui::GuiBase &gui)
{
    tgui::Theme theme;
    theme.load("assets/gui/TransparentGrey.txt");

    auto chatbox = tgui::ChatBox::create();
    chatbox->setRenderer(theme.getRenderer("ChatBox"));
    chatbox->setSize(300, 100);
    chatbox->setTextSize(18);
    chatbox->setPosition(0, 0);
    chatbox->setLinesStartFromTop();
    chatbox->addLine("This is your information box ", tgui::Color::Green);
    gui.add(chatbox, "InfoBox");
}

void GUISystem::loadMenu(tgui::GuiBase &gui)
{
    int numCols = 5;
    auto displaySize = sf::Vector2f(32, 32);

    tgui::Theme theme;
    theme.load("assets/gui/TransparentGrey.txt");
    auto menu = tgui::ChildWindow::create();
    menu->setRenderer(theme.getRenderer("ChildWindow"));
    menu->setClientSize({250, 120});
    menu->setPosition(0, 100);
    menu->setTitle("Item window");

    auto items = ItemManager::inst().getAvailableItems();
    int index = 0;
    for (auto &&item : items)
    {
        sf::Sprite sprite;
        auto &texture = EntityCreator::inst(registry).getTextureFromPath(item->getPath());
        sprite.setTexture(texture);
        auto textureSize = texture.getSize();
        if (textureSize.x > displaySize.x && textureSize.y > displaySize.y)
            sprite.setScale(displaySize.x / textureSize.x, displaySize.y / textureSize.y);
        auto canvas = tgui::CanvasSFML::create({displaySize.x, displaySize.y});
        canvas->setPosition((index % numCols) * displaySize.x, (int)(index / numCols) * displaySize.y);
        canvas->clear();
        canvas->draw(sprite);
        canvas->display();
        canvas->onClick(
            [this](shared_ptr<const Item> item)
            {
                this->isItemSelected = true;
                this->selectedItem = item;
            std::cout << item->getName() << " selected\n"; },
            item);
        menu->add(canvas);
        index++;
    }

    gui.add(menu);
}

void GUISystem::speakerUpdate()
{
    std::cout << "onSpeaker\n";

    auto aSpeaker = registry.view<Speaker>().begin();
    bool speakerOn = registry.get<Speaker>(*aSpeaker).isActive;
    ostringstream oss;
    oss << "Speakers " << (speakerOn ? "" : "de") << "activated!";
    gui.get<tgui::ChatBox>("InfoBox")->addLine(oss.str());
}

void GUISystem::onGoDanceConstruct(entt::registry &registry, entt::entity entity)
{
    std::cout << "onGoDance\n";
    auto name = registry.get<Raver>(entity).name;
    ostringstream oss;
    oss << name << "is going to dance!";
    gui.get<tgui::ChatBox>("InfoBox")->addLine(oss.str());
}

GUISystem::GUISystem(entt::registry &registry, sf::RenderWindow &window) : registry(registry), window(window), gui{window}
{
    loadChatBox(gui);
    loadMenu(gui);
    // TODO: Create a global SoundSystem component upon which GoDance gets updated.
    //  This way things get updated in the correct order.
    registry.on_construct<GoDance>().connect<&GUISystem::onGoDanceConstruct>(this);
    registry.on_update<Speaker>().connect<&GUISystem::speakerUpdate>(this);
}

void GUISystem::draw(entt::registry &registry, sf::RenderWindow &window)
{
    gui.draw();
};
