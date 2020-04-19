#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

#include "AnimationHandler.h"
#include "ITile.h"

enum class TileType { VOID, GRASS };

class Tile : public ITile
{
public:

    void SetPosition(const sf::Vector2f& pos);
    
    void AddAnim(Animation& anim) override;
    sf::RectangleShape* Get(float dt) override;
    

    Tile(const sf::Vector2f& size, std::vector<sf::Texture*> pTextures, int zLevel);
    
    ~Tile() {}

private:
    std::vector<sf::Texture*> m_pTextures;

    // Random num generator to pick random textures for the tiles
    std::random_device m_RandDev;
    std::mt19937 m_RandEngine;
    std::uniform_int_distribution<int> m_RandDist;
};

