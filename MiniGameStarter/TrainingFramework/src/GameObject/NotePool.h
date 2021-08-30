#pragma once
#include"utilities.h"
#include<deque>
class Note;
class NotePool
{
public:
	NotePool();
	NotePool(int size, int bpm, int difficulty);
	~NotePool();
	void Init(int bpm, int difficulty);
	void Draw();
	std::shared_ptr<Note> AcquireNote();
private:
	int m_poolSize;
	std::deque<std::shared_ptr<Note>> m_notePool;

};

