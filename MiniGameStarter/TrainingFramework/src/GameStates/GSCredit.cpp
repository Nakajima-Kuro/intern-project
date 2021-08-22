#include "GSCredit.h"
GSCredit::GSCredit() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listText(std::list<std::shared_ptr<Text>>{}), m_backButton(nullptr)
{
}


GSCredit::~GSCredit()
{
}



void GSCredit::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// back button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_back.tga");
	m_backButton = std::make_shared<GameButton>(model, shader, texture);
	m_backButton->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight - 100 );
	m_backButton->SetSize(192, 72);
	m_backButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});

	// game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("HeartbitXX.ttf");
	std::shared_ptr<Text> text = std::make_shared< Text>(shader, font, "Rymthm Jam", TextColor::YELLOW, 4, TextAlign::CENTER);
	text->Set2DPosition(Vector2(GLfloat(Globals::screenWidth / 2 - 170), 100));
	m_listText.push_back(text);

	// game title
	text = std::make_shared< Text>(shader, font, "This Osu!Mania cloned game is proudly made by:", TextColor::YELLOW, 2, TextAlign::CENTER);
	text->Set2DPosition(Vector2(30, 200));
	m_listText.push_back(text);
	text = std::make_shared< Text>(shader, font, "- Tran Ngoc Nam Anh (B17DCCN051)", TextColor::YELLOW, 1.5, TextAlign::CENTER);
	text->Set2DPosition(Vector2(40, 240));
	m_listText.push_back(text);
	text = std::make_shared< Text>(shader, font, "- with free assets provided by LegionGames", TextColor::YELLOW, 1.5, TextAlign::CENTER);
	text->Set2DPosition(Vector2(40, 280));
	m_listText.push_back(text);
}

void GSCredit::Exit()
{
}


void GSCredit::Pause()
{
}

void GSCredit::Resume()
{
}


void GSCredit::HandleEvents()
{
}

void GSCredit::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSCredit::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (m_backButton->HandleTouchEvents(x, y, bIsPressed))
	{
		return;
	}
}

void GSCredit::HandleMouseMoveEvents(int x, int y)
{
}

void GSCredit::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	m_backButton->Update(deltaTime);
}

void GSCredit::Draw()
{
	m_background->Draw();
	m_backButton->Draw();
	for (auto it : m_listText)
	{
		it->Draw();
	}
}