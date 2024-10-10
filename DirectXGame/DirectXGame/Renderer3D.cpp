#include "Renderer3D.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "AppWindow.h"

Renderer3D::Renderer3D(AGameObject* obj, void* shader_byte_code, size_t size_shader) : Renderer(obj, shader_byte_code, size_shader)
{
}

void Renderer3D::update()
{
	
}

void Renderer3D::draw(AppWindow* target)
{
}
