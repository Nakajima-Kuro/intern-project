#pragma once
#include"utilities.h"
#include<queue>
class Note;
class NotePool
{
public:
	NotePool();
	NotePool(int size, int bpm, int difficulty);
	~NotePool();
	void Init(int bpm, int difficulty);
	std::shared_ptr<Note> AcquireNote();
private:
	int m_poolSize;
	std::queue<std::shared_ptr<Note>> m_notePool;

};

