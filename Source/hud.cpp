#include "headers/hud.h"

namespace Game_N{

  HUD::HUD()
  {
    bordersize_ = 5;
  	width_ = 600;
  	height_ = 150;
  	startx_ = 0;
  	starty_ = 850;

  	fillColor_.r = 150;
  	fillColor_.g = 50;
  	fillColor_.b = 250;

  	borderColor_.r = 250;
  	borderColor_.r = 150;
  	borderColor_.r = 100;

  	heroMaxHp_ = 100;
  	heroHp_ = 100;
  	heroStr_ = 10;
    heroMaxMana_ = 100;
  	heroMana_= 100;
  	heroLvl_= 1;
  	heroExp_= 0;
  	heroExpToNextLvl_= 100;
    dngLvl_ = 1;
  }

  HUD::HUD(Hero &hero)
  {
    bordersize_ = 5;
  	width_ = 600;
  	height_ = 150;
  	startx_ = 0;
  	starty_ = 850;

  	fillColor_.r = 150;
  	fillColor_.g = 50;
  	fillColor_.b = 250;

  	borderColor_.r = 250;
  	borderColor_.r = 150;
  	borderColor_.r = 100;

    heroMaxHp_ = hero.getMaxHp();
    heroHp_ = hero.getHp();
    heroStr_ = hero.getDamage();
    heroMaxMana_ = hero.getMaxMana();
    heroMana_ = hero.getMana();
    heroLvl_ = hero.getLvl();
    heroExp_ = hero.getExp();
    heroExpToNextLvl_ = hero.getExpToNextLvl();
  }

  void HUD::updateStats(Hero& hero,unsigned int lvl)
  {
    heroMaxHp_ = hero.getMaxHp();
    heroHp_ = hero.getHp();
    heroStr_ = hero.getDamage();
    heroMaxMana_ = hero.getMaxMana();
    heroMana_ = hero.getMana();
    heroLvl_ = hero.getLvl();
    heroExp_ = hero.getExp();
    heroExpToNextLvl_ = hero.getExpToNextLvl();

    dngLvl_ = 0;
  }

  void HUD::drawHUD(sf::RenderWindow &window,const Hero& hero)
  {
    sf::RectangleShape rect(sf::Vector2f(width_- 2*bordersize_,height_-2*bordersize_));
  	rect.setFillColor(fillColor_);
  	rect.setOutlineThickness(bordersize_);
  	rect.setOutlineColor(borderColor_);
  	rect.setPosition(startx_+bordersize_,starty_+bordersize_);

    window.draw(rect);
  	drawStats(window,hero);
    // drawTextBox(window);
  }

  void HUD::drawStats(sf::RenderWindow & window, const Hero & hero)
  {
    std::ostringstream oss;

  	sf::Font font;
  	font.loadFromFile("resources/joystix_monospace.ttf");

  	sf::Text text;
  	text.setFont(font);
  	text.setCharacterSize(17);
  	text.setColor(sf::Color::Black);

  	oss<<"Dungeon lvl: "<<dngLvl_<<std::endl;
  	oss<<"Health: "<<hero.getHp()<<"/"<<hero.getMaxHp()<<std::endl;
    oss<<"Mana: "<<hero.getMana()<<"/"<<hero.getMaxMana()<<std::endl;
  	oss<<"Exp   : "<<hero.getExp()<<"/"<<hero.getExpToNextLvl()<<std::endl;
  	oss<<"Level : "<<hero.getLvl()<<std::endl;

  	std::string str1 = oss.str();
  	text.setString(str1);
  	text.setPosition(20,starty_+height_-bordersize_-6*5-5*20);
  	window.draw(text);
  }


}
