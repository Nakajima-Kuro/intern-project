#include "GSLibrary.h"
#include "SongButton.h"
#include "TweeningSprite2D.h"
#include "GameButton.h"
#include "Timer.h"

GSLibrary::GSLibrary()
	: GameStateBase(StateType::STATE_LIBRARY), m_position(0), m_song(nullptr), m_timer(nullptr)
{
}

GSLibrary::~GSLibrary()
{
}

void GSLibrary::Init()
{
	//Load the library
	m_library = ResourceManagers::GetInstance()->GetLibrary();


	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// background
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((GLint)Globals::screenWidth / 2, (GLint)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// back button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_back_symbol.tga");
	m_backButton = std::make_shared<GameButton>(model, shader, texture);
	m_backButton->Set2DPosition(Globals::screenWidth - 75, 75);
	m_backButton->SetSize(50, 50);
	m_backButton->SetClickSfx("click");
	m_backButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});

	//Init 3 button
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("btn_song.tga");
	//Middle button
	auto button = std::make_shared<SongButton>(model, shader, texture, m_library[0]);
	button->SetSize(650, 120);
	button->Set2DPosition(Globals::screenWidth / 2 + 50, Globals::screenHeight / 2);
	button->SetClickSfx("game_start");
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);
	//Lower button
	button = std::make_shared<SongButton>(model, shader, texture, m_library[1]);
	button->SetSize(650, 120);
	button->Set2DPosition(Globals::screenWidth / 2 + 100, Globals::screenHeight / 2 + 200);
	button->SetClickable(false);
	m_listButton.push_back(button);

	//Foreground for lower button
	texture = ResourceManagers::GetInstance()->GetTexture("spr_foreground.tga");

	auto foreground = std::make_shared<Sprite2D>(-1, model, shader, texture);
	foreground->SetSize(650, 120);
	foreground->Set2DPosition(Globals::screenWidth / 2 + 100, Globals::screenHeight / 2 + 200);
	m_listForeground.push_back(foreground);

	//Choose Arrow
	texture = ResourceManagers::GetInstance()->GetTexture("spr_arrow_choose.tga");
	m_arrow = std::make_shared<TweeningSprite2D>(model, shader, texture, 40, 0, 0.6);
	m_arrow->SetSize(50, 50);
	m_arrow->Set2DPosition(150, (GLfloat)Globals::screenHeight / 2);

	//Title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("HeartbitXX.ttf");
	m_title = std::make_shared< Text>(shader, font, "Library", TextColor::YELLOW, 4, TextAlign::CENTER);
	m_title->Set2DPosition(GLfloat(Globals::screenWidth / 2 - 80), 90);

	//Preview
	m_timer = new Timer();
	m_timer->Attach(this);
	m_song = new SoundServer(m_library[m_position]->GetPath() + ".wav");
	m_timer->start(1.5);
}

void GSLibrary::Exit()
{
	delete m_song;
	delete m_timer;
}

void GSLibrary::Pause()
{
	m_song->Stop();
	m_timer->stop();
}

void GSLibrary::Resume()
{
	m_timer->start(1.5);
}

void GSLibrary::HandleEvents()
{
}

void GSLibrary::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed) {
		if (key == VK_RETURN) {
			//Choose current song
			auto song = m_listButton[0]->GetSong();
			SharedVariableManager::GetInstance()->songName = song->GetName();
			ResourceManagers::GetInstance()->GetSfx("game_start")->Play();
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		}
		if (key == VK_UP) {
			if (m_position > 0) {
				m_position--;
				m_arrow->ResetPosition();
				ResourceManagers::GetInstance()->GetSfx("change_song")->Play();
				UpdateButtonInfo();
			}
		}
		if (key == VK_DOWN) {
			if (m_position < int(m_library.size() - 1)) {
				m_position++;
				m_arrow->ResetPosition();
				ResourceManagers::GetInstance()->GetSfx("change_song")->Play();
				UpdateButtonInfo();
			}
		}
		if (key == VK_ESCAPE) {
			ResourceManagers::GetInstance()->GetSfx("click")->Play();
			GameStateMachine::GetInstance()->PopState();
		}
	}
}

void GSLibrary::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto const& button : m_listButton) {
		button->HandleTouchEvents(x, y, bIsPressed);
	}
	m_backButton->HandleTouchEvents(x, y, bIsPressed);
}

void GSLibrary::HandleMouseMoveEvents(int x, int y)
{
}

void GSLibrary::Update(float deltaTime)
{
	m_arrow->Update(deltaTime);
	for (auto const& button : m_listButton) {
		button->Update(deltaTime);
	}
}

void GSLibrary::Draw()
{
	m_background->Draw();
	m_backButton->Draw();
	for (auto const& button : m_listButton) {
		button->Draw();
	}
	for (auto const& foreground : m_listForeground) {
		foreground->Draw();
	}
	m_title->Draw();
	m_arrow->Draw();
}

void GSLibrary::UpdateButtonInfo()
{
	m_song->Stop();
	m_listButton[0]->SetSong(m_library[m_position]);
	m_timer->start(1.5);
	if (m_position < int(m_library.size() - 1)) {
		m_listButton[1]->SetSong(m_library[m_position + 1]);
		m_listForeground[0]->SetVisible(true);
	}
	else {
		m_listButton[1]->SetSong(nullptr);
		m_listForeground[0]->SetVisible(false);
	}
}

void GSLibrary::Update(const std::string& message_from_subject)
{
	if (message_from_subject.compare("timeout") == 0) {
		m_song->ChangeSound(m_listButton[0]->GetSong()->GetPath() + ".wav");
		m_song->Play();
		m_song->Seek(40);
	}
}
