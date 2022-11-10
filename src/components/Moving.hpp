#pragma once
#include <SFML/Graphics.hpp>
#include <magic_enum.hpp>

enum class Direction
{
  up,
  down,
  left,
  right,
  nodir
};

struct Moving
{
  sf::Vector2f velocity;
  Direction direction{Direction::down};
};