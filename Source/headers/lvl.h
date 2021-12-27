#include "SFML/Graphics.hpp"
#include "enemy.h"
#include "cell.h"
// #include "summoner.h"

#pragma once

namespace Game_N{

  class Level {
    private:
        std::vector<Enemy> enemies_;
        std::vector<std::vector<Cell>> mapCell_;
    public:
        Level(std::ifstream& file, const int& dngLvl);

        int getTileType(sf::Vector2f coords) {return mapCell_[(int)(coords.y) / 100][(int)(coords.x) / 100].getCellType();}
        sf::Vector2f getHeroCoord() {
          for(int i = 0; i < mapCell_.size(); i++)
            for(int j = 0; j < mapCell_[i].size(); j++)
              if(mapCell_[i][j].getTitle() == '@')
                return sf::Vector2f(i * 110.f, j * 110.f);}

        Cell getCellType(sf::Vector2f coords) {return mapCell_[(int)(coords.y) / 100][(int)(coords.x) / 100];}

        void setTileType(sf::Vector2f coords, Cell cell) {mapCell_[(int)(coords.y) / 100][(int)(coords.x) / 100] = cell;}

        std::vector<std::vector<Cell>>& getCell(){ return mapCell_; }
        void addCell(std::vector<Cell> cell){ mapCell_.push_back(cell); }
        std::vector<Enemy>& getEnemies(){ return enemies_; }
        void addEnemy(Enemy enemy) {enemies_.push_back(enemy);}
  };
}
