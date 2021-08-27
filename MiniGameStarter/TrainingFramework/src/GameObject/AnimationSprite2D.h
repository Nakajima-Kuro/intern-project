#pragma once
#include "Sprite2D.h"
class AnimationSprite2D :
    public Sprite2D
{
protected:
    int m_numFrames;
    int m_currentFrame;
    float m_frameTime;
    float m_currentFrameTime;
    bool m_isPlaying;
public:
    AnimationSprite2D() :Sprite2D(), m_numFrames(0), m_currentFrame(0), m_frameTime(0.0f), m_currentFrameTime(0.0f), m_isPlaying(true) {};
    AnimationSprite2D(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, float frameTime);

    void		Init() override;
    void		Draw() override;
    void		Update(GLfloat deltatime) override;

    void        SetPlaying(bool isPlaying);
    bool        IsPlaying();
    void        setFrame(int frame);
};

