//
// Created by babin on 2026-05-05.
//

#ifndef CMAKESFMLPROJECT_COMBAT_H
#define CMAKESFMLPROJECT_COMBAT_H
#include <SFML/Graphics.hpp>
#include  <iostream>
#include "Rhaegal.h"

class Fight {
private:
    sf::Sprite mSprite;
    sf::IntRect mSourceRect;
    sf::Texture mTexture;
    sf::Font mFont;
    std::vector<std::string> mString;
    std::vector<sf::RectangleShape> mButtons;
    std::vector<sf::Text> mText;
    sf::RectangleShape mRect;
    sf::RectangleShape mRect2;
public:
    int mCurrentFightIndex;
    int mMaxFightOptions;
    Fight();
    void CombatLoadTexture(const std::string &filename);
    void draw(sf::RenderWindow &window);
    void menuFight();
    void ChooseAction();
};


#endif //CMAKESFMLPROJECT_COMBAT_H