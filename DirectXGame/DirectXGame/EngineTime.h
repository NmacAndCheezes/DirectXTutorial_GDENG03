#pragma once
#include "Window.h"
class EngineTime
{
public:
	void update();
	float getDT();

public: //singleton
	static EngineTime* get();

private:
	float m_old_delta = 0;
	float m_new_delta = 0;
	float m_delta_time = 0;
};
