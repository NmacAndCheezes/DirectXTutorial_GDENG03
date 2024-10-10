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
#include "Matrix4x4.h"
#include "Camera.h"
#include "CameraManager.h"
class AppWindow : public Window, public InputListener
{
public:
	AppWindow() {};

	//void update();

	~AppWindow() {};

	//Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override {};

	//Mouse
	virtual void onMouseMove(const Point& mouse_pos) override {};

	virtual void onLeftMouseDown(const Point& delta_mouse_pos) override {};
	virtual void onLeftMouseUp(const Point& delta_mouse_pos) override {};

	virtual void onRightMouseDown(const Point& delta_mouse_pos) override {};
	virtual void onRightMouseUp(const Point& delta_mouse_pos) override {};

	virtual void onFocus() override;
	virtual void onKillFocus() override;

public: //getters
	SwapChainPtr getSwapChain();
	VertexShaderPtr getVertexShader();
	PixelShaderPtr getPixelShader();
	Camera* getCamera();
	float getWidth();
	float getHeight();
private:
	SwapChainPtr m_swap_chain = NULL;
	VertexShaderPtr m_vs = NULL;
	PixelShaderPtr m_ps = NULL;
	
	CameraManager* m_cm = NULL;
	Camera* cam = NULL;
};

