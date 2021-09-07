#include "Timer.h"
#include <thread>
#include <iostream>

Timer::Timer()
	:m_timeSec(-1), timeLeft(-1), m_isStopped(true), m_isDestroyed(false)
{
}

Timer::~Timer()
{
	m_isDestroyed = true;
	stop();
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
	if (timeLeft <= 0) {
		auto thread = std::thread(&Timer::StartTimer, this);
		thread.detach();
	}
	else {
		timeLeft = m_timeSec;
		this->m_StartTime = std::chrono::steady_clock::now();
	}
}

void Timer::stop()
{
	m_isStopped = true;
}

void Timer::resume()
{
	m_isStopped = false;
}

void Timer::StartTimer()
{
	this->m_StartTime = std::chrono::steady_clock::now();
	this->timeLeft = this->m_timeSec;
	while (!m_isDestroyed) {
		if (!m_isStopped) {
			double eslapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_StartTime).count() / 1000.0;
			this->timeLeft = this->m_timeSec - eslapsedTime;
			if (this->timeLeft <= 0 && !m_isStopped) {
				m_isStopped = true;
				this->Notify("timeout");
				break;
			}
		}
	}
}
