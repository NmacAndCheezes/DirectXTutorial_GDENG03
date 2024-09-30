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

class AppWindow : public Window
{
public:
	AppWindow() {};

	//void update();

	~AppWindow() {};

	//Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	virtual void onFocus() override;
	virtual void onKillFocus() override;

public: //getters
	SwapChain* getSwapChain();
	VertexShader* getVertexShader();
	PixelShader* getPixelShader();
	ConstantBuffer* getConstantBuffer();

private:
	SwapChain* m_swap_chain = NULL;
	VertexShader* m_vs = NULL;
	PixelShader* m_ps = NULL;
	ConstantBuffer* m_cb = NULL;
private:
	Camera* cam = NULL;
	//Matrix4x4 m_world_cam;

private: //events list
	std::list<InputListener*> eventsOnFocus;
	std::list<InputListener*> eventsOnKillFocus;
};

