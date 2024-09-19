#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "InputListener.h"

class AppWindow : public Window, public InputListener
{
public:
	AppWindow() {};

	void updateQuadPosition();

	~AppWindow() {};

	//Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	virtual void onFocus() override;
	virtual void onKillFocus() override;

	//Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseDown(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseUp(const Point& delta_mouse_pos) override;
	virtual void onRightMouseDown(const Point& delta_mouse_pos) override;
	virtual void onRightMouseUp(const Point& delta_mouse_pos) override;

private:
	SwapChain* m_swap_chain = NULL;
	VertexBuffer* m_vb = NULL;
	VertexShader* m_vs = NULL;
	PixelShader* m_ps = NULL;
	ConstantBuffer* m_cb = NULL;
	IndexBuffer* m_ib = NULL;

private:
	float m_old_delta = 0;
	float m_new_delta = 0;
	float m_delta_time = 0;

	float m_delta_pos = 0;
	float m_delta_scale = 0;
	float m_delta_rot = 0;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_scale_cube = 1.0f;
};

