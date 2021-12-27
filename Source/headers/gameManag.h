#include <iostream>
#include <ctime>
#include <cmath>
#include "SFML/Graphics.hpp"
#include "hero.h"
#include "lvl.h"
#include "hud.h"

#pragma once

namespace Game_N{

  class GameManager{
    private:
        bool getExp_;
        HUD hud_;
        Hero hero_;
        std::vector<Level> levels_;
        int level_;
        sf::RenderWindow window_;
        bool W_,S_,A_,D_,Z_,X_,C_,V_,E_,HP_,MANA_;
    public:
        GameManager();
        void inputUser(sf::Keyboard::Key key, bool pressed);
        void EventType();
        void UndeadsMove();
        void EnemyMove();
        void moveHero();
        void heroCombat();
        void interactionWithMap();
        void update();
        void start();
        void Level();
    };

}
