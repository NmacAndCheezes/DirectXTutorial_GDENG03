#pragma once
#include <d3d11.h>

class DeviceContext;
class SwapChain
{
public:
	SwapChain() {}
	bool init(HWND hwnd, UINT width, UINT height);
	bool present(bool vsync);
	bool release();
	~SwapChain() {}

private:
	IDXGISwapChain* m_swap_chain = NULL;
	ID3D11RenderTargetView* m_rtv = NULL;
	ID3D11DepthStencilView* m_dsv = NULL;

private: //DeviceContext
	friend class DeviceContext;
};

