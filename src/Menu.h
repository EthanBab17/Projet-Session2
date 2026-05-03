//
// Created by babin on 2026-05-02.
//

#ifndef CMAKESFMLPROJECT_MENU_H
#define CMAKESFMLPROJECT_MENU_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
private:
    sf::Sprite mSprite;
    sf::IntRect mSourceRect;
    sf::Texture mTexture;


public:
    sf::Font mFont;
    int mCurrentMenuIndex;
    const int mMaxMenuOptions = 2;
    std::vector<std::string> mMenuOptions;
    Menu();
    void draw(sf::RenderWindow &window);
    void menuLoadTexture(const std::string &filename);
    void setPosition(sf::Vector2f position);
    void setOptions();
};


#endif //CMAKESFMLPROJECT_MENU_H