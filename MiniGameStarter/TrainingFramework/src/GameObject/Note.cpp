#include "Note.h"
#include "ResourceManagers.h"
#include "AnimationSprite2D.h"

Note::Note()
	: m_spawnLocation(Vector2()), m_finishLocation(Vector2()), m_speed(0), m_bpm(0), m_difficulty(4)
{
	Init();
}

Note::Note(Vector2 spawnPosition, Vector2 finishPosition, float bpm, int difficulty)
	: m_spawnLocation(spawnPosition), m_finishLocation(finishPosition), m_speed(0), m_bpm(bpm), m_difficulty(difficulty)
{
	Init();
}

Note::~Note()
{
	delete m_sprite;
}

void Note::Init()
{
	//Init 3 arrow sprite
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Arrow/Left/spr_note.tga");
	m_sprite = new AnimationSprite2D(model, shader, texture, 3, 0.0f);
	m_sprite->SetPlayAnimation(false);
	//Caculate speed
	m_speed = float(m_finishLocation.y - m_spawnLocation.y) / (60.0f / m_bpm * m_difficulty);
}

void Note::Update(float deltaTime)
{
	if (Globals::screenHeight + m_sprite->GetHeight() < m_position.y) {
		Destroy("");
	}
	else {
		Set2DPosition(m_position.x, m_position.y + m_speed * deltaTime);
		Area2D::Update(deltaTime);
	}
}

void Note::Draw()
{
	m_sprite->Draw();
	Area2D::Draw();
}

void Note::SetLane(int lane)
{
	m_sprite->setFrame(lane);
}

void Note::Destroy(std::string status)
{
	m_sprite->SetVisible(false);
	if (strcmp(status.c_str(), "") != 0) {
		//Being destroy by ArrowButton
		//Emit Particles here
	}
}
