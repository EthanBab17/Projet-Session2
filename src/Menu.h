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
    std::vector<std::string> mString;


public:
    std::vector<sf::RectangleShape> mButtons;
    sf::Font mFont;
    int mCurrentMenuIndex;
    const int mMaxMenuOptions = 2;
    std::vector<sf::Text> mMenuOptions;
    Menu();
    void init(float x, float y);
    void draw(sf::RenderWindow &window);
    void menuLoadTexture(const std::string &filename);
    void setPosition(sf::Vector2f position);
    void setOptions();
};


#endif //CMAKESFMLPROJECT_MENU_H