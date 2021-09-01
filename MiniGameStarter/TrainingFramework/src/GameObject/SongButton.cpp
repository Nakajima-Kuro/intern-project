#include "SongButton.h"
#include "ResourceManagers.h"
#include "Song.h"
#include "Text.h"

SongButton::SongButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, std::shared_ptr<Song> song)
	:AnimationSprite2D(model, shader, texture, 1, 0.4f), m_song(song), m_clickable(true)
{
	Init();
}

SongButton::SongButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: AnimationSprite2D(model, shader, texture, 1, 0.4f), m_song(nullptr), m_clickable(true)
{
	Init();
}

SongButton::~SongButton()
{
}

void SongButton::Init()
{
	AnimationSprite2D::SetPlayAnimation(false);
	auto font = ResourceManagers::GetInstance()->GetFont("HeartbitXX.ttf");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");

	m_textName = std::make_shared<Text>(shader, font, "", TextColor::YELLOW, 2);
	m_textBpm = std::make_shared<Text>(shader, font, "", TextColor::YELLOW, 2);
	m_textDifficulty = std::make_shared<Text>(shader, font, "", TextColor::YELLOW, 2);
	LoadSongInfo();
}

bool SongButton::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	bool isHandled = false;
	if (m_clickable) {
		if (bIsPressed)
		{
			setFrame(1);
			if ((x > m_position.x - m_iWidth / 2) && (x < m_position.x + m_iWidth / 2)
				&& (y > m_position.y - m_iHeight / 2) && (y < m_position.y + m_iHeight / 2))
			{
				// The button is being pressed down
			}
		}
		else
		{
			setFrame(0);
			if ((x > m_position.x - m_iWidth / 2) && (x < m_position.x + m_iWidth / 2)
				&& (y > m_position.y - m_iHeight / 2) && (y < m_position.y + m_iHeight / 2))
			{
				// Only perform click action when the same button was pressed down and released
				//Handle click here
				isHandled = true;
			}
		}
	}
	return isHandled;
}

void SongButton::Draw()
{
	AnimationSprite2D::Draw();
	m_textName->Draw();
	m_textBpm->Draw();
	m_textDifficulty->Draw();
}

void SongButton::SetClickable(bool isClickable)
{
	m_clickable = isClickable;
}

bool SongButton::IsClickable()
{
	return m_clickable;
}

void SongButton::Set2DPosition(Vector2 position)
{
	SetSongInfoPosition(position.x, position.y);
	AnimationSprite2D::Set2DPosition(position);
}

void SongButton::Set2DPosition(GLint x, GLint y)
{
	SetSongInfoPosition(x, y);
	AnimationSprite2D::Set2DPosition(x, y);
}

void SongButton::SetSongInfoPosition(GLint x, GLint y)
{
	m_textName->Set2DPosition(x - m_iWidth / 2 + 20, y - m_iHeight / 2 + 20);
	m_textBpm->Set2DPosition(x + m_iWidth / 2 - 40, y - m_iHeight / 2 + 20);
	m_textDifficulty->Set2DPosition(x - m_iWidth / 2 + 20, y + m_iHeight / 2 - 20);
}

std::shared_ptr<Song> SongButton::GetSong()
{
	return m_song;
}

void SongButton::SetSong(std::shared_ptr<Song> song)
{
	m_song = song;
	LoadSongInfo();
}

void SongButton::LoadSongInfo()
{
	if (m_song != nullptr) {
		SetVisible(true);

		m_textName->SetText(m_song->GetName());
		m_textBpm->SetText("BPM: " + std::to_string(m_song->GetBpm()));
		m_textDifficulty->SetText(std::to_string(m_song->GetDifficulty()));
	}
	else {
		SetVisible(false);
		m_textName->SetText("");
		m_textBpm->SetText("");
		m_textDifficulty->SetText("");
	}
}
