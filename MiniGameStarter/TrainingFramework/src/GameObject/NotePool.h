#pragma once
#include"utilities.h"
class Note;
class NotePool
{
public:
	NotePool();
	NotePool(int size, int bpm, int difficulty);
	~NotePool();
	void Init(int bpm, int difficulty);
	void Draw();
	void Update(float deltaTime);

	std::shared_ptr<Note> AcquireNote();
	std::list<std::shared_ptr<Note>> GetListNote();
private:
	int m_poolSize;
	std::list<std::shared_ptr<Note>> m_notePool;

};

