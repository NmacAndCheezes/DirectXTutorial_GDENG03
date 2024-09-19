#pragma once
#include <d3d11.h>

class DeviceContext;

class VertexBuffer
{
public:
	VertexBuffer() :m_layout(0), m_buffer(0) {}
	bool load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader);
	bool release();
	UINT getSizeVertexList();
	~VertexBuffer() {}
private:
	UINT m_size_vertex = 0;
	UINT m_size_list = 0;
private:
	ID3D11Buffer* m_buffer = NULL;
	ID3D11InputLayout* m_layout = NULL;
private:
	friend class DeviceContext;
};