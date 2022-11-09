#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include <string>
#include <unordered_map>
using std::shared_ptr;
using std::string;
using std::unordered_map;

class AnimationAdapter
{
private:
    // shared_ptr<sf::Texture> texture;

public:
    // AnimationAdapter(shared_ptr<sf::Texture> texture);

    static unordered_map<string, Animation> getAnimations(sf::Texture &texture);
};