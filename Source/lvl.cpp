#include "headers/lvl.h"

namespace Game_N{

    Level::Level(std::ifstream& file, const int& dngLvl)
    {
      std::string str;
      int y = 0;
      while(file.is_open() && getline(file, str))
          {
              std::vector<Cell> cell;
              for(int x = 0; x < str.size(); x++)
              {
                  if(str[x] == '#')
                  {
                          cell.emplace_back(sf::Vector2f(x, y), 0, sf::Color::Cyan,str[x]);
                  }

                  else if(str[x] == '.')
                  {
                          cell.emplace_back(sf::Vector2f(x, y), 1,sf::Color::Green,str[x]);
                  }

                  else if(str[x] == 'l')
                  {
                          cell.emplace_back(sf::Vector2f(x,y), 2,sf::Color::Yellow,str[x]);
                  }
                  else if(str[x] == '@')
                  {
                          cell.emplace_back(sf::Vector2f(x, y), 3,sf::Color::Green,str[x]);
                  }
                  else if(str[x] == '+'){
                          cell.emplace_back(sf::Vector2f(x, y), 4,sf::Color(255,228,205),str[x]);
                    }
                  else if(str[x] == '-'){
                          cell.emplace_back(sf::Vector2f(x, y), 5,sf::Color(128,218,235),str[x]);
                      }
                  else if(str[x] == 'g'){
                        enemies_.emplace_back(dngLvl,3,14, false,"ghoul", sf::Vector2f(x, y),sf::Color(255,73,108));
                        cell.emplace_back(sf::Vector2f(x, y), 6, sf::Color(2, 255, 0),str[x]);
                      }
                  else if(str[x] == 'o'){
                        enemies_.emplace_back(dngLvl,2,10, false, "ork", sf::Vector2f(x, y),sf::Color(255,180,231));
                        cell.emplace_back(sf::Vector2f(x, y), 7, sf::Color(2, 255, 0),str[x]);
                      }
                else if(str[x] == 's'){
                        enemies_.emplace_back(dngLvl,5,15, false, "skeleton", sf::Vector2f(x, y),sf::Color(125,127,125));
                        cell.emplace_back(sf::Vector2f(x, y), 7, sf::Color(2, 255, 0),str[x]);
                      }
                  else if(str[x] == 'z'){
                        enemies_.emplace_back(dngLvl,2,17, true, "zombie", sf::Vector2f(x, y),sf::Color(178,236,93));
                        cell.emplace_back(sf::Vector2f(x, y), 8, sf::Color(2, 255, 0),str[x]);
                      }
                  else if(str[x] == 'S'){
                        enemies_.emplace_back(dngLvl,2,8, false, "summoner", sf::Vector2f(x, y),sf::Color(148,0,211));
                        cell.emplace_back(sf::Vector2f(x, y), 9, sf::Color(2, 255, 0),str[x]);
                      }
                  else if(str[x] == 'G'){
                        enemies_.emplace_back(dngLvl,2,3, false, "golemL", sf::Vector2f(x, y),sf::Color(123,11,234));
                        cell.emplace_back(sf::Vector2f(x, y), 10, sf::Color(2, 255, 0),str[x]);
                      }
                    else
                      continue;
                  }
              mapCell_.emplace_back(cell);
              y++;
            }

  }
}
