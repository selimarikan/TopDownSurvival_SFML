#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "AnimationHandler.h"
#include "ITile.h"

enum class MapDirection { LEFT, UP, RIGHT, DOWN };

class Character : public ITile
{
public:

    void SetPosition(const sf::Vector2f& pos);

    void AddAnim(Animation& anim) override;
    sf::RectangleShape* Get(float dt) override;

    Character(const sf::Vector2f& size, 
        sf::Texture* stand_left, 
        sf::Texture* stand_top, 
        sf::Texture* stand_right, 
        sf::Texture* stand_bottom,
        sf::Texture* move_left01,
        sf::Texture* move_left02,
        sf::Texture* move_up01,
        sf::Texture* move_up02,
        sf::Texture* move_right01,
        sf::Texture* move_right02,
        sf::Texture* move_down01,
        sf::Texture* move_down02,
        int zLevel): m_CurrentDirection(MapDirection::LEFT), m_IsMoving(false)
    {
        m_Shape.setSize(size);
        m_StandSprites.reserve(4);
        m_StandSprites.emplace_back(stand_left);
        m_StandSprites.emplace_back(stand_top);
        m_StandSprites.emplace_back(stand_right);
        m_StandSprites.emplace_back(stand_bottom);

        m_MoveSprites.reserve(8);
        m_MoveSprites.emplace_back(move_left01);
        m_MoveSprites.emplace_back(move_left02);
        m_MoveSprites.emplace_back(move_up01);
        m_MoveSprites.emplace_back(move_up02);
        m_MoveSprites.emplace_back(move_right01);
        m_MoveSprites.emplace_back(move_right02);
        m_MoveSprites.emplace_back(move_down01);
        m_MoveSprites.emplace_back(move_down02);

        ZLevel = zLevel;

        // Set the initial sprite
        Turn(MapDirection::DOWN);
    }

    void Turn(MapDirection dir);
    
    void Move(MapDirection dir); //(const sf::Vector2f& relativeDist)

private:
    MapDirection m_CurrentDirection;

    // Left, up, right, bottom
    std::vector<sf::Texture*> m_StandSprites;
    
    // L1, L2, U1, U2, R1, R2, B1, B2
    std::vector<sf::Texture*> m_MoveSprites;

    bool m_IsMoving;

};

