#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>

#pragma once

namespace Game_N{

  class Cell {
    private:
        sf::RectangleShape rectangle_;
        sf::Vector2f coord_;
        int cell_;
        char title_;
    public:
        Cell();
        Cell(sf::Vector2f coords, int cell, sf::Color color, char title);
        sf::Vector2f getCoords(){ return rectangle_.getPosition(); };
        void setRectangle(sf::RectangleShape rect) {rectangle_ = rect;}
        sf::RectangleShape& getRectangle(){ return rectangle_; };
        int getCellType() { return cell_; };
        void setCellType(int cell) {cell_ = cell;}
        void setCell(int ch){ cell_ = ch; };
        char& getTitle() {return title_;}
        void setCoords(sf::Vector2f coords){ rectangle_.setPosition(coords); };
  };

}
