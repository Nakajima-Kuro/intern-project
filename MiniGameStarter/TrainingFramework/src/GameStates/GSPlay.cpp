#include "GSPlay.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Area2D.h"
#include "Text.h"
#include "GameButton.h"
#include "Conductor.h"
#include "ArrowButton.h"
#include "Note.h"
#include "NotePool.h"

GSPlay::GSPlay()
	:m_conductor(nullptr), m_currentMapPosition(0), m_notePool(nullptr)
{

}


GSPlay::~GSPlay()
{
	delete m_conductor;
	delete m_notePool;
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// background
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play_1.tga");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((GLint)Globals::screenWidth / 2, (GLint)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_back_symbol.tga");
	m_backButton = std::make_shared<GameButton>(model, shader, texture);
	m_backButton->Set2DPosition(Globals::screenWidth - 50, 50);
	m_backButton->SetSize(50, 50);
	m_backButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});

	//LeftArrow
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Arrow/spr_arrow_button_left.tga");
	auto button = std::make_shared<ArrowButton>("arrow", model, shader, texture, VK_LEFT);
	button->Set2DPosition(Globals::screenWidth / 2 - 120, m_arrowButtonY);
	button->SetSize(96, 96);
	button->Attach(this);
	m_listArrowButton.push_back(button);

	//UpArrow
	texture = ResourceManagers::GetInstance()->GetTexture("Arrow/spr_arrow_button_up.tga");
	button = std::make_shared<ArrowButton>("arrow", model, shader, texture, VK_UP);
	button->Set2DPosition(Globals::screenWidth / 2, m_arrowButtonY);
	button->SetSize(96, 96);
	button->Attach(this);
	m_listArrowButton.push_back(button);

	//RightArrow
	texture = ResourceManagers::GetInstance()->GetTexture("Arrow/spr_arrow_button_right.tga");
	button = std::make_shared<ArrowButton>("arrow", model, shader, texture, VK_RIGHT);
	button->Set2DPosition(Globals::screenWidth / 2 + 120, m_arrowButtonY);
	button->SetSize(96, 96);
	button->Attach(this);
	m_listArrowButton.push_back(button);

	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("HeartbitXX.ttf");
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	// score text
	m_textScore = std::make_shared<Text>(shader, font, "Score: 0", TextColor::YELLOW, 2);
	m_textScore->Set2DPosition(Vector2(20, 40));

	// combo text
	m_textCombo = std::make_shared<Text>(shader, font, "", TextColor::YELLOW, 2);
	m_textCombo->Set2DPosition(Vector2(20, 75));

	////Add the note to scene
	//m_note = std::make_shared<Note>(GetSpawnPosition(1), m_listArrowButton[1]->Get2DPosition(), 150, 4);
	//m_note->SetLane(1);
	//m_note->SetSize(96, 96);
	//m_note->SetActive(true);
	//m_listNote.push_back(m_note);

	//Load the song and the beat map     Not done!!!
	//Hard code
	m_beatMap = {
		{5, 0, 0, 0, 0},
		{16, 1, 1, 1, 0},
		{40, 1, 1, 1, 1},
		{76, 2, 2, 2, 0},
		{106, 1, 0, 0, 1},
		{200, 2, 2, 2, 1},
		{306, 1, 1, 1, 0},
		{442, 2, 2, 2, 0},
		{474, 0, 1, 1, 1},
		{556, 0, 2, 2, 1},
		{600, 1, 1, 1, 1},
		{626, 0, 0, 0, 0},
		{628, 2, 0, 0, 0},
		{640, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	};

	//Init the NotePool
	m_notePool = new NotePool(15, 150, 4);

	//Play the song
	this->m_conductor = new Conductor(150, 4, m_songName + ".wav");
	this->m_conductor->Attach(this);
	this->m_conductor->PlayWithBeatOffset(2);
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
	for (auto button : m_listArrowButton) {
		button->HandleKeyEvents(key, bIsPressed);
	}
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
	for (auto it : m_listArrowButton)
	{
		it->Update(deltaTime);
		it->checkCollision(m_listNote);
	}
	m_conductor->Update(deltaTime);
	for (auto const& note : m_listNote) {
		note->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_textScore->Draw();
	m_textCombo->Draw();
	m_backButton->Draw();
	for (auto it : m_listArrowButton)
	{
		it->Draw();
	}
	//m_note->Draw();
	m_notePool->Draw();
}

void GSPlay::Update(const std::string& message_from_subject)
{
	//Trigger every beat
	if (strcmp(message_from_subject.c_str(), "beat") == 0) {
		//If the next beat == the next beat in the map, advance counter by 1 to step to next phase in the map
		if (m_conductor->GetBeat() == m_beatMap[m_currentMapPosition][0] - 1) {
			m_currentMapPosition++;
		}
		if (m_beatMap[m_currentMapPosition][0] == 0) {
			//End game and transit to score screen here
		}
	}

	//Trigger every beat in loop of measures
	if (strcmp(message_from_subject.c_str(), "measure") == 0) {
		std::vector<int> spawnedPosition;
		int spawnPosition = rand() % 3; //Get random lane for not spawning (0, 1, 2)
		for (int i = 0; i < m_beatMap[m_currentMapPosition][m_conductor->GetMeasure()]; i++) {
			//Spawn the note base on the current number in the beat map
			while (std::find(spawnedPosition.begin(), spawnedPosition.end(), spawnPosition) != spawnedPosition.end()) {
				//Keep ramdoming until we got a free lane. Dont want 2 note spawned in one lane, huh? :))
				spawnPosition = rand() % 3;
			}
			spawnedPosition.push_back(spawnPosition);
			//Add the note to scene
			//auto note = std::make_shared<Note>(GetSpawnPosition(spawnPosition), m_listArrowButton[spawnPosition]->Get2DPosition(), 150, 4);
			auto note = m_notePool->AcquireNote();
			note->SetLane(spawnPosition);
			note->Set2DPosition(GetSpawnPosition(spawnPosition));
			note->SetFinishPosition(m_listArrowButton[spawnPosition]->Get2DPosition());
			note->SetActive(true);
			m_listNote.push_back(note);
		}
	}
	if (strcmp(message_from_subject.c_str(), "arrow_perfect") == 0) {
		IncreaseScore(3);
	}
	if (strcmp(message_from_subject.c_str(), "arrow_good") == 0) {
		IncreaseScore(2);
	}
	if (strcmp(message_from_subject.c_str(), "arrow_okay") == 0) {
		IncreaseScore(1);
	}
	if (strcmp(message_from_subject.c_str(), "arrow") == 0) {
		IncreaseScore(0);
	}
}

Vector2 GSPlay::GetSpawnPosition(int position)
{
	return Vector2(m_listArrowButton[position]->Get2DPosition().x, 30);
}

void GSPlay::IncreaseScore(int num)
{
	//Handle the score and TextScore
	m_score += num;
	m_textScore->SetText("Score: " + std::to_string(m_score));
	//Handle combo and TextCombo
	if (num == 0) {
		//Miss the note => lose combo
		if (m_maxCombo < m_combo) {
			m_maxCombo = m_combo;
		}
		m_combo = 0;
		m_textCombo->SetText("");
	}
	else {
		m_combo++;
		if (m_combo >= 10) {
			m_textCombo->SetText("Combo " + std::to_string(m_combo));
		}
	}
}


