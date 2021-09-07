#pragma once
#include<chrono>
#include"ISubject.h"
class Timer
	:public ISubject
{
public:
	Timer();
	virtual ~Timer();

	double timeLeft;

	bool is_stopped();
	void start(double timeSec);
	void start();
	void stop();
	void resume();
private:
	double m_timeSec;
	bool m_isStopped;
	bool m_isDestroyed;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
	void StartTimer();
};

