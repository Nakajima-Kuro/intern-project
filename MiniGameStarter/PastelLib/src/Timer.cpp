#include "Timer.h"

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
	return timeLeft <= 0 ? true : false;
}

void Timer::start(double timeSec)
{
	this->m_timeSec = timeSec;
	this->start();
}

void Timer::start()
{
	this->m_StartTime = std::chrono::steady_clock::now();
	this->timeLeft = this->m_timeSec;
	while (true) {
		double eslapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_StartTime).count() / 1000000.0;
		this->timeLeft = this->m_timeSec - eslapsedTime;
		if (this->timeLeft <= 0) {
			this->Notify("timeout");
			break;
		}
	}
}
