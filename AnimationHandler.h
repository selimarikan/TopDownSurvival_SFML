#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Animation
{
public:
    unsigned int StartFrame;
    unsigned int EndFrame;

    float Duration;

    Animation(unsigned int startFrame, unsigned int endFrame, float duration)
    {
        StartFrame = startFrame;
        EndFrame = endFrame;
        Duration = duration;
    }

    unsigned int GetLength()
    {
        return EndFrame - StartFrame + 1;
    }
};

class AnimationHandler
{
private:
    std::vector<Animation> m_Animations;

    // Current time since the animation loop started
    float m_T;
    int m_CurrentAnim;
    int m_CurrentFrame;

public:
    void AddAnim(Animation& anim);

    // Update the current frame of animation. dt is the time since 
    // the update was last called (time for one frame to be executed).
    int Update(const float dt);

    // Change the animation, resetting t in the process.
    void ChangeAnim(unsigned int animNum);

    int GetAnimCount() 
    {
        return m_Animations.size();
    }

    AnimationHandler() : m_CurrentFrame(0), m_CurrentAnim(-1), m_T(0.0f)
    {
    }
};

