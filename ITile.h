#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "AnimationHandler.h"

class ITile
{
public:
    virtual ~ITile() {}
    virtual sf::RectangleShape* Get(float dt) = 0;
    virtual void AddAnim(Animation& anim) = 0;
    
    int ZLevel;

protected:
    sf::RectangleShape m_Shape;
    AnimationHandler m_AnimHandler;

};

