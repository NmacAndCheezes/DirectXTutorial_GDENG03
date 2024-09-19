#include "EngineTime.h"

void EngineTime::update()
{
	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount64();

	m_delta_time = m_old_delta ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}

float EngineTime::getDT()
{
	return m_delta_time;
}

EngineTime* EngineTime::get()
{
	static EngineTime time;
	return &time;
}
