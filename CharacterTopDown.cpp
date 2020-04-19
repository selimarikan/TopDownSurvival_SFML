#include "CharacterTopDown.h"

void CharacterTopDown::SetPosition(const sf::Vector2f& pos)
{
    m_Shape.setPosition(pos);
}

void CharacterTopDown::AddAnim(Animation& anim)
{
    m_AnimHandler.AddAnim(anim);
}

// Sets the correct sprite from the animation result and returns the shape to be rendered
sf::RectangleShape* CharacterTopDown::Get(float dt)
{
    int frame = m_AnimHandler.Update(dt);
    // int spriteIndex = ((int)m_CurrentDirection * 2) + frame;
    m_Shape.setTexture(m_StandSprites[0]);

    return &m_Shape;
}

sf::Vector2f CharacterTopDown::GetPosition()
{
    return m_Shape.getPosition();
}

void CharacterTopDown::SetRotation(float deg)
{
    m_Shape.setRotation(deg);
}

void CharacterTopDown::Turn(float deg)
{
    // sf::Texture* pTex = m_StandSprites[0];
    // m_Shape.setTexture(pTex);
    m_Shape.rotate(deg);
    // m_CurrentDirection = dir;
    // m_AnimHandler.ChangeAnim((unsigned int)dir);
    // m_Shape.setTexture(m_StandSprites[(int)m_CurrentDirection]);
}

void CharacterTopDown::Move(MapDirection dir)
{
    sf::Vector2f dist;
    // Every direction has 2 sprites, use 
    // int sprIndex = ((int)dir) * 2;

    if (dir == MapDirection::LEFT)
    {
        dist.x = -32.0f;
    }
    else if (dir == MapDirection::UP)
    {
        dist.y = -32.0f;
    }
    else if (dir == MapDirection::RIGHT)
    {
        dist.x = 32.0f;
    }
    else if (dir == MapDirection::DOWN)
    {
        dist.y = 32.0f;
    }

    // Update moving sprite
    // m_Shape.setTexture(m_MoveSprites[sprIndex]);

    // Actually move the object
    m_Shape.move(dist);
}
