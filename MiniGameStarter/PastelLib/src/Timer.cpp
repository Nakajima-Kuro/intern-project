#include "Timer.h"
#include <thread>

Timer::Timer()
{
	this->m_timeSec = -1;
	this->timeLeft = -1;
}

Timer::~Timer()
{
}

bool Timer::is_stopped()
{
	return m_isStopped;
}

void Timer::start(double timeSec)
{
	this->m_timeSec = timeSec;
	this->start();
}

void Timer::start()
{
	m_isStopped = false;
	auto thread = std::thread(&Timer::StartTimer, this);
	thread.detach();
}

void Timer::stop()
{
	m_isStopped = true;
}

void Timer::StartTimer()
{
	this->m_StartTime = std::chrono::steady_clock::now();
	this->timeLeft = this->m_timeSec;
	while (true && !m_isStopped) {
		double eslapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_StartTime).count() / 1000.0;
		this->timeLeft = this->m_timeSec - eslapsedTime;
		if (this->timeLeft <= 0) {
			m_isStopped = true;
			this->Notify("timeout");
			break;
		}
	}
}
