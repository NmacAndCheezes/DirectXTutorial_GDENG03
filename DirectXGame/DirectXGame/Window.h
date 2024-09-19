#pragma once
#include <Windows.h>

class Window
{
public:
	Window() {};
	bool init();
	bool broadcast();
	bool release();
	bool isRunning();
	~Window() {};

	RECT getClientWindowRect();
	void SetHWND(HWND hwnd);

	//Events
	virtual void onCreate() {};
	virtual void onUpdate() {};
	virtual void onDestroy();
	virtual void onFocus() {};
	virtual void onKillFocus() {};
protected:
	HWND m_hwnd = NULL; //handle
	bool m_is_running = false;

};

