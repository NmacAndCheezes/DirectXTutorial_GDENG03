#pragma once
#pragma once
#include <d3d11.h>

class DeviceContext;

class IndexBuffer
{
public:
	IndexBuffer() : m_buffer(0) {}
	bool load(void* list_indices, UINT size_list);
	bool release();
	UINT getSizeIndexList();
	~IndexBuffer() {}
private:
	UINT m_size_list = 0;
private:
	ID3D11Buffer* m_buffer = NULL;
private:
	friend class DeviceContext;
};
