//
// Created by babin on 2026-05-01.
//

#ifndef CMAKESFMLPROJECT_ENTITIES_H
#define CMAKESFMLPROJECT_ENTITIES_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Entities {
protected:
    sf::IntRect mSourceRect;
    sf::Texture mTexture;
    sf::FloatRect mhitbox;
    std::vector<sf::FloatRect> mhitboxes;
    sf::Vector2f mPosition;
    sf::Sprite mSprite;
public:
    Entities():mSprite(mTexture){};
    virtual ~Entities() = default;
    void loadTexture(const std::string &filename);
    void draw(sf::RenderWindow &window);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    void setSprite(sf::Sprite sprite);
    sf::Sprite getSprite();
    sf::Vector2f getSpritePosition();
    void setSpriteScale(sf::Vector2f scale);
    sf::Vector2f getSpriteScale();
    void setOrigin(sf::Vector2f origin);
    sf::FloatRect getBounds();
    sf::FloatRect getHitbox();
    void setHitboxPos(sf::Vector2f hitboxPos);
};


#endif //CMAKESFMLPROJECT_ENTITIES_H