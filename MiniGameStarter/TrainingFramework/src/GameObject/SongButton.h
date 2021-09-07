#pragma once
#include "AnimationSprite2D.h"

class Song;
class Text;
class SoundServer;

class SongButton :
    public AnimationSprite2D
{
public:
    SongButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, std::shared_ptr<Song> song);
    SongButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
    ~SongButton();
    void Init();
    bool HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
    void Draw();

    void SetClickable(bool isClickable);
    bool IsClickable();
    void SetOnClick(void (*pBtClick)());
    void SetClickSfx(std::string name);
    void Set2DPosition(Vector2 position);
    void Set2DPosition(GLint x, GLint y);
    void SetSongInfoPosition(GLint x, GLint y);

    std::shared_ptr<Song> GetSong();
    void SetSong(std::shared_ptr<Song> song);
    void LoadSongInfo();

private:
    std::shared_ptr<Song>                   m_song;
    std::shared_ptr<Text>		            m_textName;
    std::shared_ptr<Text>		            m_textBpm;
    std::shared_ptr<Text>		            m_textDifficulty;
    std::shared_ptr<Text>		            m_textHighscore;
    std::shared_ptr<Text>		            m_textMaxCombo;
    std::list<std::shared_ptr<Sprite2D>>    m_listStar;
    std::shared_ptr<SoundServer>            m_clickingSfx;

    bool                                    m_clickable;
    bool                                    m_isHolding;

    void	                                (*m_pBtClick)();
};

