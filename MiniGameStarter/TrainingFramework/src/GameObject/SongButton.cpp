#include "SongButton.h"
#include "ResourceManagers.h"
#include "Song.h"
#include "Text.h"

#include <sstream>

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
	m_textBpm = std::make_shared<Text>(shader, font, "", TextColor::YELLOW, 1.7);
	m_textDifficulty = std::make_shared<Text>(shader, font, "", TextColor::YELLOW, 1.7);
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
	for (auto const& star : m_listStar) {
		star->Draw();
	}
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
	m_textName->Set2DPosition(x - m_iWidth / 2 + 30, y - m_iHeight / 2 + 40);
	m_textBpm->Set2DPosition(x + m_iWidth / 2 - 150, y + m_iHeight / 2 - 20);
	m_textDifficulty->Set2DPosition(x - m_iWidth / 2 + 30, y + m_iHeight / 2 - 20);
	int i = 0;
	for (auto const& star : m_listStar) {
		star->Set2DPosition(x - m_iWidth / 2 + 150 + 40 * i, y + m_iHeight / 2 - 30);
		i++;
	}
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
		//Set song name
		m_textName->SetText(m_song->GetName());

		//Set song BPM
		std::stringstream ss;
		ss << m_song->GetBpm();
		m_textBpm->SetText("BPM: " + ss.str());

		//Set song difficulty
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("spr_star.tga");
		m_textDifficulty->SetText("Difficulty: ");

		m_listStar.clear();
		for (int i = 0; i < m_song->GetDifficulty(); i++) {
			auto star = std::make_shared<Sprite2D>(model, shader, texture);
			star->SetSize(30, 26);
			star->Set2DPosition(GetPosition().x - m_iWidth / 2 + 150 + 40 * i, GetPosition().y + m_iHeight / 2 - 30);
			m_listStar.push_back(star);
		}
	}
	else {
		SetVisible(false);
		m_textName->SetText("");
		m_textBpm->SetText("");
		m_textDifficulty->SetText("");
		for (auto const& star : m_listStar) {
			star->SetVisible(false);
		}
	}
}
