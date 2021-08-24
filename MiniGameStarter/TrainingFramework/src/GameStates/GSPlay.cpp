#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// background
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play_1.tga");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button clode
	texture = ResourceManagers::GetInstance()->GetTexture("btn_back_symbol.tga");
	m_backButton = std::make_shared<GameButton>(model, shader, texture);
	m_backButton->Set2DPosition(Globals::screenWidth - 50, 50);
	m_backButton->SetSize(50, 50);
	m_backButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});

	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("HeartbitXX.ttf");
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	// score title
	m_scoreTitle = std::make_shared< Text>(shader, font, "Score:", TextColor::YELLOW, 2);
	m_scoreTitle->Set2DPosition(Vector2(20, 40));

	// score
	m_score = std::make_shared< Text>(shader, font, "0", TextColor::YELLOW, 2);
	m_score->Set2DPosition(Vector2(130, 40));

	// score title
	m_comboTitle = std::make_shared< Text>(shader, font, "Combo:", TextColor::YELLOW, 2);
	m_comboTitle->Set2DPosition(Vector2(20, 75));

	// score
	m_combo = std::make_shared< Text>(shader, font, "0", TextColor::YELLOW, 2);
	m_combo->Set2DPosition(Vector2(130, 75));

}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_backButton->HandleTouchEvents(x, y, bIsPressed);
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	m_backButton->Update(deltaTime);
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_score->Draw();
	m_scoreTitle->Draw();
	m_combo->Draw();
	m_comboTitle->Draw();
	m_backButton->Draw();
}