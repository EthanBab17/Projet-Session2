//
// Created by babin on 2026-04-27.
//

#ifndef CMAKESFMLPROJECT_PLAYER_H
#define CMAKESFMLPROJECT_PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream> 

class Player {
private:
    sf::IntRect mSourceRect;
    sf::Texture mTexture;
    sf::Sprite mSprite;
public:
    Player();
    void loadTexture(const std::string& filename);
    void setDirection(int index);
    void setPosition(sf::Vector2f position);
    void draw(sf::RenderWindow& window);
    void move(sf::Vector2f offset);
};


#endif //CMAKESFMLPROJECT_PLAYER_H