#include "NotePool.h"
#include"Note.h"

NotePool::NotePool()
	:m_poolSize(0)
{
	Init(0, 0);
}

NotePool::NotePool(int size, int bpm, int difficulty)
	: m_poolSize(size)
{
	Init(bpm, difficulty);
}

NotePool::~NotePool()
{
	while (!m_notePool.empty())
	{
		m_notePool.pop();
	}
}

void NotePool::Init(int bpm, int difficulty)
{
	for (int i = 0; i < m_poolSize; i++) {
		std::shared_ptr<Note> note = std::make_shared<Note>(Vector2(-100, -100), Vector2(-100, -100), bpm, difficulty);
		note->SetSize(96, 96);
		note->Draw();
		m_notePool.push(note);
	}
}

std::shared_ptr<Note> NotePool::AcquireNote()
{
	std::shared_ptr<Note> note = m_notePool.front();
	m_notePool.pop();
	m_notePool.push(note);
	return note;
}
