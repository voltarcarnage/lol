#include "headers/gameManag.h"

namespace Game_N{

  GameManager::GameManager(): hero_(), level_(0)
  {
    hud_ = HUD();
    window_.create(sf::VideoMode(1000, 1000), "Necromancer");
    std::ifstream txt;
    int number = 1;
    while(1)
    {
      txt.open("level/" + std::to_string(number) + ".txt");
      if(txt.is_open())
      {
        levels_.emplace_back(txt,level_);
        number++;
        txt.close();
      }
      else
        break;
    }
    hero_.setCoords(levels_[level_].getHeroCoord());
    getExp_ = false;
    W_ = false; S_ = false; A_ = false; D_ = false; Z_ = false; X_ = false; C_ = false; V_ = false; E_ = false; HP_ = false; MANA_ = false;
  }

  void GameManager::update()
  {
    window_.clear();
    for(int i = 0; i < levels_[level_].getCell().size(); i++)
        for(int j = 0; j < levels_[level_].getCell()[i].size(); j++){
           window_.draw(levels_[level_].getCell()[i][j].getRectangle());
       }
       for(int i = 0; i < hero_.getUndeads().size(); i++)
       {
         window_.draw(hero_.getUndeads()[i].getCell().getRectangle());
         window_.draw(hero_.getUndeads()[i].getText());
       }
    for(int i = 0; i < levels_[level_].getEnemies().size(); i++)
    {
        window_.draw(levels_[level_].getEnemies()[i].getCell().getRectangle());
        window_.draw(levels_[level_].getEnemies()[i].getText());
    }

    window_.draw(hero_.getShape());
    hud_.drawHUD(window_,hero_);
    window_.setKeyRepeatEnabled(false);
    window_.display();
  }

  void GameManager::EventType()
  {
    sf::Event event;
    while(window_.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
                window_.close();
        else if(event.type == sf::Event::KeyPressed)
                inputUser(event.key.code, true);
        else if(event.type == sf::Event::KeyReleased)
                inputUser(event.key.code, false);
        else
            continue;
    }
  }

  void GameManager::inputUser(sf::Keyboard::Key key, bool pressed)
  {
    if(key == sf::Keyboard::W)
        W_ = pressed;
    else if(key == sf::Keyboard::A)
        A_ = pressed;
    else if(key == sf::Keyboard::S)
        S_ = pressed;
    else if(key == sf::Keyboard::D)
        D_ = pressed;
    else if(key == sf::Keyboard::Z)
        Z_ = pressed;
    else if(key == sf::Keyboard::X)
        X_ = pressed;
    else if(key == sf::Keyboard::C)
        C_ = pressed;
    else if(key == sf::Keyboard::V)
        V_ = pressed;
    else if(key == sf::Keyboard::E)
        E_ = pressed;
    else if(key == sf::Keyboard::H)
        HP_ = pressed;
    else if(key == sf::Keyboard::M)
        MANA_ = pressed;
  }

  void GameManager::interactionWithMap()
  {
    for(int i = 0; i < levels_[level_].getCell().size(); i++)
        for(int j = 0; j <  levels_[level_].getCell()[i].size(); j++)
        {
          if(levels_[level_].getCell()[i][j].getCellType() == 0)
          {
            if(hero_.getShape().getGlobalBounds().intersects(levels_[level_].getCell()[i][j].getRectangle().getGlobalBounds()))
            {
              if(W_)
              {
                sf::Vector2f vec;
                vec = hero_.getCoords();
                vec.y += 5 * hero_.getSpeed();
                hero_.setCoords(vec);
              }
              else if(S_)
              {
                sf::Vector2f vec;
                vec = hero_.getCoords();
                vec.y -= 5 * hero_.getSpeed();
                hero_.setCoords(vec);
              }
              else if(D_)
              {
                sf::Vector2f vec;
                vec = hero_.getCoords();
                vec.x -= 5 * hero_.getSpeed();
                hero_.setCoords(vec);
              }
              else if(A_)
              {
                sf::Vector2f vec;
                vec = hero_.getCoords();
                vec.x += 5 * hero_.getSpeed();
                hero_.setCoords(vec);
              }
            }
          }
          else if(levels_[level_].getCell()[i][j].getCellType() == 2)
          {
            if(hero_.getShape().getGlobalBounds().intersects(levels_[level_].getCell()[i][j].getRectangle().getGlobalBounds()))
            {
              std::cout << "ttrue";
              hero_.takeDamage(1);
            }
          }

        }
  }

  void GameManager::heroCombat()
  {
    Cell cell;
    for(int i = 0; i < levels_[level_].getCell().size(); i++){
        for(int j = 0; j < levels_[level_].getCell()[i].size(); j++)
        {
          if(levels_[level_].getCell()[i][j].getCellType() == 2){
            cell = levels_[level_].getCell()[i][j];
            break;
          }
        }
        break;
    }
    for(int i = 0; i < levels_[level_].getEnemies().size(); i++)
    {
      sf::Vector2f vect = levels_[level_].getEnemies()[i].getCell().getRectangle().getPosition();
      if(hero_.detectEnemy(vect) && hero_.getMana() > 0)
      {
        if(Z_)
        {
          hero_.decreaseMana(hero_.getSpell("curse",vect)->getManaCost());
          if(!levels_[level_].getEnemies()[i].takeDamage(hero_.getSpell("curse",vect)->getDmgBySpell()))
          {
            levels_[level_].getEnemies()[i].die();
            if(levels_[level_].getEnemies()[i].getName() == "golemL")
            {
              levels_[level_].setTileType(vect, cell);
            }
            if(levels_[level_].getEnemies()[i].getState()){
              auto iter = levels_[level_].getEnemies().cbegin();
              levels_[level_].getEnemies().erase(iter + i);
            }
            getExp_ = true;
          }
          Z_ = false;
        }
        else if(X_)
        {
          if(!levels_[level_].getEnemies()[i].isAlive())
          {
            if(HP_)
            {
              hero_.castASpell("desiccationH",levels_[level_].getEnemies()[i]);
              auto iter = levels_[level_].getEnemies().cbegin();
              levels_[level_].getEnemies().erase(iter + i);
            }
            else if(MANA_)
            {
              hero_.castASpell("desiccationM",levels_[level_].getEnemies()[i]);
              auto iter = levels_[level_].getEnemies().cbegin();
              levels_[level_].getEnemies().erase(iter + i);
            }
          }
        }
        else if(C_)
        {
          if(!levels_[level_].getEnemies()[i].isAlive())
          {
            if(hero_.getUndeads().size() <= hero_.getUndeadsCount()){
            hero_.castASpell("necromancy", levels_[level_].getEnemies()[i]);
            auto iter = levels_[level_].getEnemies().cbegin();
            levels_[level_].getEnemies().erase(iter + i);
            }
          }
          C_ = false;
        }
      }

      if(!levels_[level_].getEnemies()[i].isAlive() && getExp_)
      {
        getExp_ = false;
        hero_.gainExp(20);
      }
    }

    for(int i = 0; i < hero_.getUndeads().size(); i++)
    {
      if(V_)
      {
        hero_.castASpell("morphism",hero_.getUndeads()[i]);
        V_ = false;
      }
    }

  }

  void GameManager::UndeadsMove()
    {
      int quot = 0;
      for(int i = 0 ; i < hero_.getUndeads().size(); i++) {
        sf::Vector2f vec = hero_.getUndeads()[i].getCell().getRectangle().getPosition();
              for(int k = 0; k < levels_[level_].getCell().size(); k++)
                for(int p = 0; p <  levels_[level_].getCell()[k].size(); p++){
                  if(levels_[level_].getCell()[k][p].getCellType() == 0){
                      if(!(hero_.getUndeads()[i].getCell().getRectangle().getGlobalBounds().intersects(levels_[level_].getCell()[k][p].getRectangle().getGlobalBounds())))
                    {
                 for(int j = 0; j < levels_[level_].getEnemies().size(); j++)
                 {
                   if(levels_[level_].getEnemies()[i].isAlive())
                    hero_.getUndeads()[i].move(levels_[level_].getEnemies()[i].getCell().getRectangle().getPosition());
                  else
                  {
                    ++quot;
                    if(!(quot % 2)){
                      hero_.getUndeads()[i].move(hero_.getCoords() + sf::Vector2f(15.f,15.f));
                      continue;
                    }
                    else
                      hero_.getUndeads()[i].move(hero_.getCoords() + sf::Vector2f(15.f,15.f));
                  }


                }
                 if(levels_[level_].getEnemies().empty())
                 {
                    ++quot;
                   if(!(quot % 2)){
                     hero_.getUndeads()[i].move(hero_.getCoords() + sf::Vector2f(15.f,15.f));
                    continue;
                   }
                   else
                     hero_.getUndeads()[i].move(hero_.getCoords() + sf::Vector2f(15.f,15.f));
                }
              }
              else
              {
                sf::Vector2f vector = hero_.getUndeads()[i].getPos();
                vector.x -= 20;
                vector.y -= 20;
                 hero_.getUndeads()[i].move(vector);
              }
              }
              }
      for(int i = 0; i < hero_.getUndeads().size(); i++) {
        for(int j = 0; j < levels_[level_].getEnemies().size(); j++){
          float dist = sqrt(pow(hero_.getUndeads()[i].getCell().getRectangle().getPosition().x - levels_[level_].getEnemies()[j].getCell().getRectangle().getPosition().x, 2) + pow(hero_.getUndeads()[i].getCell().getRectangle().getPosition().y - levels_[level_].getEnemies()[j].getCell().getRectangle().getPosition().y, 2));
          if (dist <= 200.f) {
              if(levels_[level_].getEnemies()[j].isAlive()){
                if(!levels_[level_].getEnemies()[j].takeDamage(hero_.getUndeads()[i].getDamage())){
                  levels_[level_].getEnemies()[j].die();
                  getExp_ = true;
                  }
                }
                if(!levels_[level_].getEnemies()[j].isAlive() && getExp_)
                {
                  getExp_ = false;
                  hero_.gainExp(20);
                }
                break;
            }
          }
        }

        hero_.getUndeads()[i].getFont().loadFromFile("resources/ShareTech.ttf");

        hero_.getUndeads()[i].getText().setFont(hero_.getUndeads()[i].getFont());
        hero_.getUndeads()[i].getText().setCharacterSize(25);
        hero_.getUndeads()[i].getText().setColor(sf::Color::Black);

        hero_.getUndeads()[i].getText().setString(hero_.getUndeads()[i].getName());
        hero_.getUndeads()[i].getText().setPosition(hero_.getUndeads()[i].getCell().getRectangle().getPosition().x, hero_.getUndeads()[i].getCell().getRectangle().getPosition().y + 25);

      }
    }


  void GameManager::EnemyMove()
  {
    for(int i = 0 ; i < levels_[level_].getEnemies().size(); i++) {
      sf::Vector2f vec = levels_[level_].getEnemies()[i].getCell().getRectangle().getPosition();
      if(levels_[level_].getEnemies()[i].isAlive())
            for(int k = 0; k < levels_[level_].getCell().size(); k++)
              for(int p = 0; p <  levels_[level_].getCell()[k].size(); p++){
                if(levels_[level_].getCell()[k][p].getCellType() == 0){
                    if(!(levels_[level_].getEnemies()[i].getCell().getRectangle().getGlobalBounds().intersects(levels_[level_].getCell()[k][p].getRectangle().getGlobalBounds())))
                  {
                  levels_[level_].getEnemies()[i].move(hero_.getShape().getPosition());
            }
            else
            {
              sf::Vector2f vector = hero_.getShape().getPosition();
              vector.x -= 20;
              vector.y -= 20;
              levels_[level_].getEnemies()[i].move(vector);
            }
            }
            }
    for(int i = 0; i < levels_[level_].getEnemies().size(); i++)
    {
        float dist = sqrt(pow(levels_[level_].getEnemies()[i].getCell().getRectangle().getPosition().x - hero_.getShape().getPosition().x, 2) + pow(levels_[level_].getEnemies()[i].getCell().getRectangle().getPosition().y - hero_.getShape().getPosition().y, 2));
        if (dist <= 200.f)
        {
          hero_.takeDamage(levels_[level_].getEnemies()[i].getDamage());
          break;
          }
      }

      levels_[level_].getEnemies()[i].getFont().loadFromFile("resources/ShareTech.ttf");

      levels_[level_].getEnemies()[i].getText().setFont(levels_[level_].getEnemies()[i].getFont());
      levels_[level_].getEnemies()[i].getText().setCharacterSize(25);
      levels_[level_].getEnemies()[i].getText().setColor(sf::Color::Black);

      levels_[level_].getEnemies()[i].getText().setString(levels_[level_].getEnemies()[i].getName());
      levels_[level_].getEnemies()[i].getText().setPosition(levels_[level_].getEnemies()[i].getCell().getRectangle().getPosition().x, levels_[level_].getEnemies()[i].getCell().getRectangle().getPosition().y + 25);

    }
  }


  void GameManager::Level()
  {
    for(int i = 0; i < levels_[level_].getCell().size(); i++)
        for(int j = 0; j <  levels_[level_].getCell()[i].size(); j++)
        {
          if(levels_[level_].getCell()[i][j].getCellType() == 4)
          {
            if(hero_.getShape().getGlobalBounds().intersects(levels_[level_].getCell()[i][j].getRectangle().getGlobalBounds()))
            {
              if(E_)
              {
                  ++level_;
                  E_ = false;
              }
            }
          }
          else if(levels_[level_].getTileType(hero_.getCoords()) == 5)
          {
            if(hero_.getShape().getGlobalBounds().intersects(levels_[level_].getCell()[i][j].getRectangle().getGlobalBounds()))
            {
              if(E_) {
                  --level_;
                  E_ = false;
              }
            }
          }

        }
  }

  void GameManager::moveHero()
  {
    if(W_)
    {
      sf::Vector2f vec;
      vec = hero_.getCoords();
      vec.y -= hero_.getSpeed();
      hero_.setCoords(vec);
    }
    else if(S_)
    {
      sf::Vector2f vec;
      vec = hero_.getCoords();
      vec.y += hero_.getSpeed();
      hero_.setCoords(vec);
    }
    else if(D_)
    {
      sf::Vector2f vec;
      vec = hero_.getCoords();
      vec.x += hero_.getSpeed();
      hero_.setCoords(vec);
    }
    else if(A_)
    {
      sf::Vector2f vec;
      vec = hero_.getCoords();
      vec.x -= hero_.getSpeed();
      hero_.setCoords(vec);
    }
  }

  void GameManager::start()
  {
    window_.setFramerateLimit(30);
    while(window_.isOpen() && hero_.isAlive())
    {
        EventType();
        interactionWithMap();
        moveHero();
        EnemyMove();
        heroCombat();
        UndeadsMove();
        update();
        Level();
    }
  }


}
