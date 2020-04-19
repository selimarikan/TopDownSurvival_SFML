#include "Tile.h"

Tile::Tile(const sf::Vector2f& size, std::vector<sf::Texture*> pTextures, int zLevel)
{
    // Random num for texture picking
    m_RandEngine = std::mt19937(m_RandDev());
    m_RandDist = std::uniform_int_distribution(0, (int)pTextures.size() - 1);

    m_Shape.setSize(size);
    m_pTextures = pTextures;

    // Get a random texture from the list
    m_Shape.setTexture(pTextures[m_RandDist(m_RandEngine)]);
    ZLevel = zLevel;
}

void Tile::AddAnim(Animation& anim)
{
    m_AnimHandler.AddAnim(anim);
    m_AnimHandler.ChangeAnim(m_AnimHandler.GetAnimCount() - 1);
}

// Get the current sprite depending on the animation delta
sf::RectangleShape* Tile::Get(float dt)
{
    // Only update if any anim frames are there
    if (m_AnimHandler.GetAnimCount() > 0)
    {
        int frame = m_AnimHandler.Update(dt);
        int spriteIndex = frame;
        m_Shape.setTexture(m_pTextures[spriteIndex]);
    }

    return &m_Shape;
}


void Tile::SetPosition(const sf::Vector2f& pos)
{
    m_Shape.setPosition(pos);
}
