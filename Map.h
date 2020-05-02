#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Tile.h"

class Map
{
public:
    Map(unsigned int width, unsigned int height, unsigned int tileSize);
    void Build();
    void AddTexture(const std::string &name, std::vector<sf::Texture *> pTexture);
    std::vector<Tile *> GetTiles();

private:
    unsigned int m_Width;
    unsigned int m_Height;
    float m_TileSize;

    std::vector<Tile *> m_pTiles;
    std::unordered_map<std::string, std::vector<sf::Texture *>> m_pTextures;
};
