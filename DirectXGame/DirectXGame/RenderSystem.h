#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "Prerequisites.h"
#include <vector>
#include "AppWindow.h"
#include "Renderer.h"

class RenderSystem
{
public:
	RenderSystem();
	bool init();
	bool release();
	~RenderSystem();

public: //Get other classes
	SwapChainPtr createSwapChain(HWND hwnd, UINT width, UINT height);
	DeviceContextPtr getImmediateDeviceContext();
	VertexBufferPtr createVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
	VertexShaderPtr createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PixelShaderPtr createPixelShader(const void* shader_byte_code, size_t byte_code_size);
	ConstantBufferPtr createConstantBuffer(void* buffer, UINT size_buffer);
	IndexBufferPtr createIndexBuffer(void* list_indices, UINT size_list);

public: //shaders
	//vertex shader
	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void releaseCompiledShader();


public:
	void registerRenderer(Renderer* rend);
	//void removeRenderer(Renderer* rend);
	void draw(AppWindow* target);
private: //DeviceContext
	DeviceContextPtr m_imm_device_context = NULL;

private: //Graphics
	ID3D11Device* m_d3d_device = NULL;
	D3D_FEATURE_LEVEL m_feature_level = (D3D_FEATURE_LEVEL)NULL;

private: //SwapChain
	IDXGIDevice* m_dxgi_device = NULL;
	IDXGIAdapter* m_dxgi_adapter = NULL;
	IDXGIFactory* m_dxgi_factory = NULL;
	ID3D11DeviceContext* m_imm_context = NULL;

private:
	ID3DBlob* m_blob = nullptr;
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

private:
	std::vector<Renderer*> renderer_list;
private:
	friend class SwapChain;
	friend class VertexBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class ConstantBuffer;
	friend class IndexBuffer;
};

