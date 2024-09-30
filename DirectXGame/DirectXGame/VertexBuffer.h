#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class VertexBuffer
{
public:
	VertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader, RenderSystem* system);
	UINT getSizeVertexList();
	~VertexBuffer();
private:
	UINT m_size_vertex = 0;
	UINT m_size_list = 0;
private:
	ID3D11Buffer* m_buffer = NULL;
	ID3D11InputLayout* m_layout = NULL;
	RenderSystem* m_system = nullptr;

private:
	friend class DeviceContext;
};