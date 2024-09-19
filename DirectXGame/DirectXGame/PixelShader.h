#pragma once
#include <d3d11.h>
class GraphicsEngine;
class DeviceContext;

//info per pixel
class PixelShader
{
public:
	PixelShader() {}
	void release();
	~PixelShader() {}
private:
	bool init(const void* shader_byte_code, size_t byte_code_size);
private:
	ID3D11PixelShader* m_ps = NULL;
private:
	friend class GraphicsEngine;
	friend class DeviceContext;
};



