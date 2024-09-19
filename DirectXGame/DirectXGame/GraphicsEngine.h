#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>

class SwapChain;
class DeviceContext;
class VertexBuffer;
class VertexShader;
class PixelShader;
class ConstantBuffer;
class IndexBuffer;

class GraphicsEngine
{
public:
	GraphicsEngine() {}
	bool init();
	bool release();
	~GraphicsEngine() {}
public: //Get other classes
	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();
	VertexBuffer* createVertexBuffer();
	VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);
	ConstantBuffer* createConstantBuffer();
	IndexBuffer* createIndexBuffer();
public: //singleton
	static GraphicsEngine* get();

public: //shaders
	//vertex shader
	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void releaseCompiledShader();

private: //DeviceContext
	DeviceContext* m_imm_device_context = NULL;

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
	friend class SwapChain;
	friend class VertexBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class ConstantBuffer;
	friend class IndexBuffer;
};

