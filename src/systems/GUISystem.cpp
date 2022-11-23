#include "GUISystem.hpp"

void GUISystem::handleEvent(sf::Event event)
{
    gui.handleEvent(event);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isItemSelected)
    {
        auto mousePos = sf::Mouse::getPosition(window);
        if (mousePos.x < 0 || mousePos.x > WINDOW_WIDTH || mousePos.y < 0 || mousePos.y > WINDOW_HEIGHT)
            return;
        auto ptr = selectedItem.lock();
        placeItem(ptr, mousePos);
    }
}

void GUISystem::placeItem(shared_ptr<const Item> item, sf::Vector2i mousePos)
{
    // TODO: Bug with the position when the window is moved
    // TODO: Verify that you don't click on the menu;
    try
    {
        TmxWriter::inst().addObject(item->getName(), mousePos, registry);
        isItemSelected = false;
        ostringstream oss;
        oss << item->getName() << " added!";
        gui.get<tgui::ChatBox>("InfoBox")->addLine(oss.str());
    }
    catch (const char *exception)
    {
        gui.get<tgui::ChatBox>("InfoBox")->addLine(exception);
    }
}

void GUISystem::loadChatBox(tgui::GuiBase &gui)
{
    auto chatbox = tgui::ChatBox::create();
    chatbox->setRenderer(theme.getRenderer("ChatBox"));
    chatbox->setSize(300, 100);
    chatbox->setTextSize(18);
    chatbox->setPosition(0, 0);
    chatbox->setLinesStartFromTop();
    chatbox->addLine("This is your information box ", tgui::Color::Green);
    gui.add(chatbox, "InfoBox");
}

void GUISystem::loadItemMenu(tgui::GuiBase &gui)
{
    int numCols = 5;
    auto displaySize = sf::Vector2f(32, 32);

    auto menu = tgui::ChildWindow::create();
    menu->setRenderer(theme.getRenderer("ChildWindow"));
    menu->setClientSize({250, 120});
    menu->setPosition(0, 100);
    menu->setTitle("Item menu");

    auto items = ItemManager::inst().getAvailableItems();
    int index = 0;
    for (auto &&item : items)
    {
        sf::Sprite sprite;
        auto &texture = EntityCreator::inst().getTextureFromPath(item->getPath());
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

void GUISystem::loadMusicMenu(tgui::GuiBase &gui)
{
    // auto musicFiles = ItemManager::inst().getMusicFiles();
    auto listBox = tgui::ListBox::create();
    listBox->setRenderer(theme.getRenderer("ListBox"));
    listBox->setSize(250, 120);
    listBox->setItemHeight(24);
    listBox->setPosition(10, 340);
    listBox->addItem("Item 1");
    listBox->addItem("Item 2");
    listBox->addItem("Item 3");
    listBox->onDoubleClick([this]()
                           { engine->onSongSelect("dummy text"); });
    gui.add(listBox);
}

void GUISystem::speakerUpdate()
{
    auto rig = registry.view<SoundRig>().begin();
    bool speakersOn = registry.get<SoundRig>(*rig).isActive;
    ostringstream oss;
    oss << "Speakers " << (speakersOn ? "" : "de") << "activated!";
    gui.get<tgui::ChatBox>("InfoBox")->addLine(oss.str());
}

void GUISystem::onGoDanceConstruct(entt::registry &registry, entt::entity entity)
{
    auto name = registry.get<Raver>(entity).name;
    ostringstream oss;
    oss << name << " is going to dance!";
    gui.get<tgui::ChatBox>("InfoBox")->addLine(oss.str());
}

GUISystem::GUISystem(entt::registry &registry, sf::RenderWindow &window, shared_ptr<Engine> engine)
    : registry(registry), window(window), gui{window}, engine(engine)
{
    theme.load("assets/gui/TransparentGrey.txt");

    loadChatBox(gui);
    loadItemMenu(gui);
    loadMusicMenu(gui);
    registry.on_update<SoundRig>().connect<&GUISystem::speakerUpdate>(this);
    registry.on_construct<GoDance>().connect<&GUISystem::onGoDanceConstruct>(this);
}

void GUISystem::draw(entt::registry &registry, sf::RenderWindow &window)
{
    gui.draw();
};
