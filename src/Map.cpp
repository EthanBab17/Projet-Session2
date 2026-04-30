//
// Created by babin on 2026-04-29.
//

#include "Map.h"

bool Map::load(const std::string& tilesetPath, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height) {
    if (!tileTexture.loadFromFile(tilesetPath)) return false;

    tile.setPrimitiveType(sf::PrimitiveType::Triangles);
    tile.resize(width * height * 6); // 2 triangles par tuile = 6 points

    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            int tileNumber = tiles[i + j * width];

            // Coordonnées dans le tileset
            int tu = tileNumber % (tileTexture.getSize().x / tileSize.x);
            int tv = tileNumber / (tileTexture.getSize().x / tileSize.x);

            sf::Vertex* triangles = &tile[(i + j * width) * 6];

            // On définit les 6 points pour former deux triangles (un carré)
            // Positions des coins
            sf::Vector2f p1(i * tileSize.x, j * tileSize.y);
            sf::Vector2f p2((i + 1) * tileSize.x, j * tileSize.y);
            sf::Vector2f p3(i * tileSize.x, (j + 1) * tileSize.y);
            sf::Vector2f p4((i + 1) * tileSize.x, (j + 1) * tileSize.y);

            // Coordonnées de texture
            sf::Vector2f t1(tu * tileSize.x, tv * tileSize.y);
            sf::Vector2f t2((tu + 1) * tileSize.x, tv * tileSize.y);
            sf::Vector2f t3(tu * tileSize.x, (tv + 1) * tileSize.y);
            sf::Vector2f t4((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);

            // Triangle 1
            triangles[0] = {p1, t1};
            triangles[1] = {p2, t2};
            triangles[2] = {p3, t3};
            // Triangle 2
            triangles[3] = {p3, t3};
            triangles[4] = {p2, t2};
            triangles[5] = {p4, t4};
        }
    }
    return true;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.texture = &tileTexture;
    target.draw(tile, states);
}