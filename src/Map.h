//
// Created by babin on 2026-04-29.
//

#ifndef CMAKESFMLPROJECT_MAP_H
#define CMAKESFMLPROJECT_MAP_H
#include<SFML/Graphics.hpp>

class Map: public sf::Drawable {
    private:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
    sf::Texture tileTexture;
    sf::VertexArray tile;

    public:
    bool load(const std::string& tilesetPath, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
};


#endif //CMAKESFMLPROJECT_MAP_H