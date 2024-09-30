#pragma once
#include "InputListener.h"
#include <unordered_set>
#include "Point.h"
class InputSystem
{
public:
	void update();
	void addListner(InputListener* listener);
	void removeListner(InputListener* listener);

	void setCursorPosition(const Point& pos);
	void showCursor(bool show);
public: //singleton
	static InputSystem* get();
	static void initialize();
	static void destroy();

private:
	static InputSystem* sharedInstance;
	InputSystem() {}
	InputSystem(InputSystem const&) {}
	InputSystem& operator=(InputSystem const&) {};
	~InputSystem();

private:
	std::unordered_set<InputListener*> m_set_listeners;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};
	Point m_old_mouse_pos;
	bool m_first_time = true;

};