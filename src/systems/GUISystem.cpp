#include "GUISystem.hpp"

void GUISystem::handleEvent(sf::Event event)
{
    gui.handleEvent(event);
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

void GUISystem::selectItem()
{
    std::cout << "Tree selected\n";
}

void GUISystem::loadMenu(tgui::GuiBase &gui)
{

    sf::Sprite sprite;
    auto &texture = EntityCreator::inst(registry).getTextureFromPath("assets/map/objects/tree_01.png");
    sprite.setTexture(texture);
    auto size = texture.getSize();
    auto canvas = tgui::CanvasSFML::create({size.x, size.y});
    canvas->setPosition(0, 100);
    canvas->clear();
    canvas->draw(sprite);
    canvas->display();
    canvas->onClick(&GUISystem::selectItem, this);
    gui.add(canvas);
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

GUISystem::GUISystem(entt::registry &registry, sf::RenderWindow &window) : registry(registry), gui{window}
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
