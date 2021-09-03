#include "GSScore.h"
#include "GameButton.h"
#include "SongButton.h"

GSScore::GSScore()
	:GameStateBase(StateType::STATE_SCORE)
{
}

GSScore::~GSScore()
{
}

void GSScore::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	//Song Info
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("btn_song.tga");
	m_songTitle = std::make_shared<SongButton>(model, shader, texture, ResourceManagers::GetInstance()->GetSong(SharedVariableManager::GetInstance()->songName));
	m_songTitle->SetSize(650, 120);
	m_songTitle->SetClickable(false);
	m_songTitle->Set2DPosition(Globals::screenWidth / 2, 100);

	// retry button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_retry_symbol.tga");
	auto button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2 - 100, Globals::screenHeight - 70);
	button->SetSize(80, 80);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopAndReloadState();
		});
	m_listButton.push_back(button);

	// to library button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_exit_symbol.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2 + 100, Globals::screenHeight - 70);
	button->SetSize(80, 80);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopBackToState(StateType::STATE_LIBRARY);
		});
	m_listButton.push_back(button);

	//Score
	GLfloat basePosition = 250;
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("HeartbitXX.ttf");
	std::shared_ptr<Text> text = std::make_shared< Text>(shader, font, "Score: " + SharedVariableManager::GetInstance()->score, TextColor::YELLOW, 3.2f, TextAlign::CENTER);
	text->Set2DPosition(m_marginLeft, basePosition - 10);
	m_listText.push_back(text);

	//Perfect
	text = std::make_shared< Text>(shader, font, "Perfect: " + SharedVariableManager::GetInstance()->perfect, TextColor::YELLOW, 2, TextAlign::CENTER);
	text->Set2DPosition(m_marginLeft, basePosition + 60);
	m_listText.push_back(text);

	//Good
	text = std::make_shared< Text>(shader, font, "Good: " + SharedVariableManager::GetInstance()->good, TextColor::YELLOW, 2, TextAlign::CENTER);
	text->Set2DPosition(m_marginLeft + 250, basePosition + 60);
	m_listText.push_back(text);

	//Okay
	text = std::make_shared< Text>(shader, font, "Okay: " + SharedVariableManager::GetInstance()->okay, TextColor::YELLOW, 2, TextAlign::CENTER);
	text->Set2DPosition(m_marginLeft, basePosition + 120);
	m_listText.push_back(text);

	//Miss
	text = std::make_shared< Text>(shader, font, "Miss: " + SharedVariableManager::GetInstance()->miss, TextColor::YELLOW, 2, TextAlign::CENTER);
	text->Set2DPosition(m_marginLeft + 250, basePosition + 120);
	m_listText.push_back(text);

	//Max Combo
	text = std::make_shared< Text>(shader, font, "Max combo: " + SharedVariableManager::GetInstance()->maxCombo, TextColor::YELLOW, 2, TextAlign::CENTER);
	text->Set2DPosition(m_marginLeft, basePosition + 180);
	m_listText.push_back(text);

	//Rank title
	text = std::make_shared< Text>(shader, font, "Rank: ", TextColor::YELLOW, 1.5, TextAlign::CENTER);
	text->Set2DPosition(Globals::screenWidth - 370.f, 400);
	m_listText.push_back(text);

	//Rank
	font = ResourceManagers::GetInstance()->GetFont("Heartbit-Bold.otf");
	text = std::make_shared< Text>(shader, font, "S", TextColor::YELLOW, 10, TextAlign::CENTER);
	text->Set2DPosition(Globals::screenWidth - 300.f, 400);
	m_listText.push_back(text);
}

void GSScore::Exit()
{
}

void GSScore::Pause()
{
}

void GSScore::Resume()
{
}

void GSScore::HandleEvents()
{
}

void GSScore::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSScore::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto const& button : m_listButton) {
		button->HandleTouchEvents(x, y, bIsPressed);
	}
}

void GSScore::HandleMouseMoveEvents(int x, int y)
{
}

void GSScore::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto const& button : m_listButton) {
		button->Update(deltaTime);
	}
}

void GSScore::Draw()
{
	m_background->Draw();
	m_songTitle->Draw();
	for (auto it : m_listText)
	{
		it->Draw();
	}
	for (auto const& button : m_listButton) {
		button->Draw();
	}
}
