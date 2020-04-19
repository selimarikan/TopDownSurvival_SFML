#include "AnimationHandler.h"
#include <iostream>

void AnimationHandler::AddAnim(Animation& anim)
{
    m_Animations.push_back(anim);
}

int AnimationHandler::Update(const float dt)
{
    if ((m_CurrentAnim >= m_Animations.size()) || (m_CurrentAnim < 0))
    {
        return m_CurrentFrame;
    }

    float duration = m_Animations[m_CurrentAnim].Duration;

    // Stop at the last frame
    if (m_CurrentFrame > m_Animations[m_CurrentAnim].GetLength())
    {
        return m_CurrentFrame;
    }

    // Check if the anim has progressed to a new frame and if so, change the next frame
    if (int((m_T + dt) / duration) > int(m_T / duration))
    {
        // Calculate the frame number
        m_CurrentFrame = int((m_T + dt) / duration);

        // Adjust for looping
        m_CurrentFrame %= m_Animations[m_CurrentAnim].GetLength();
        std::cout << "CurrentAnim: " << m_CurrentAnim << " CurrentFrame: " << m_CurrentFrame << "  m_T: " << m_T << "\n";
    }

    // Increment the time elapsed
    m_T += dt;

    // Adjust for looping
    if (m_T > duration * m_Animations[m_CurrentAnim].GetLength())
    {
        m_T = 0.0f;
    }

    return m_CurrentFrame;
}

void AnimationHandler::ChangeAnim(unsigned int animNum)
{
    // Do not change the animation if the animation is currently active or the new animation does not exist.
    if ((m_CurrentAnim == animNum) || (animNum >= m_Animations.size()) || (animNum < 0))
    {
        return;
    }

    // Set the current animation
    m_CurrentAnim = animNum;

    m_T = 0.0f;
}
