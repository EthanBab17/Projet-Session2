//
// Created by babin on 2026-05-01.
//

#ifndef CMAKESFMLPROJECT_ENTITIES_H
#define CMAKESFMLPROJECT_ENTITIES_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Entities {
public:
    sf::IntRect mSourceRect;
    sf::Texture mTexture;
    sf::FloatRect mhitbox;
    std::vector<sf::FloatRect> mhitboxes;
    sf::Vector2f mPosition;
    sf::Sprite mSprite;

    Entities():mSprite(mTexture){};
    virtual ~Entities() = default;
    void loadTexture(const std::string &filename);
    void draw(sf::RenderWindow &window);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    void setSprite(sf::Sprite sprite);
    sf::Sprite getSprite();
};


#endif //CMAKESFMLPROJECT_ENTITIES_H