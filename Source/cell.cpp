#include "headers/cell.h"

namespace Game_N{

  Cell::Cell()
  {
    coord_ = {0, 0};
    rectangle_ = sf::RectangleShape(sf::Vector2f(40, 40));
    cell_ = 0;
  }

  Cell::Cell(sf::Vector2f coords, int cell, sf::Color color, char title)
  {
    rectangle_ = sf::RectangleShape(sf::Vector2f(100, 100));
    rectangle_.setOutlineColor(sf::Color::Black);
    rectangle_.setOutlineThickness(true);
    rectangle_.setFillColor(color);
    rectangle_.setPosition(coords.x * 100, coords.y * 100);
    title_ = title;
    cell_ = cell;
  }

}
