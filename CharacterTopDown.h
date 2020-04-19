#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "AnimationHandler.h"
#include "ITile.h"

enum class MapDirection { LEFT, UP, RIGHT, DOWN };

class CharacterTopDown : public ITile
{
public:

    void SetPosition(const sf::Vector2f& pos);

    void AddAnim(Animation& anim) override;
    sf::RectangleShape* Get(float dt) override;

    // For top-down single character
    CharacterTopDown(const sf::Vector2f& size, sf::Texture* stand, int zLevel): m_IsMoving(false)
    {
        m_Shape.setSize(size);
        m_StandSprites.emplace_back(stand);
        ZLevel = zLevel;
        // Move the origin to the center of the object for trafos
        m_Shape.setOrigin(size.x / 2.0, size.y / 2.0);
    }

    void Turn(float deg);
    
    void Move(MapDirection dir); //(const sf::Vector2f& relativeDist)
    sf::Vector2f GetPosition();
    void SetRotation(float deg);

private:
    // MapDirection m_CurrentDirection;

    // Single sprite, rotate the sprite for movement
    std::vector<sf::Texture*> m_StandSprites;

    bool m_IsMoving;
};

