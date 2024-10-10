#include "Renderer2D.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "AppWindow.h"

Renderer2D::Renderer2D(AGameObject* obj, void* shader_byte_code, size_t size_shader) : Renderer(obj, shader_byte_code, size_shader)
{
}

void Renderer2D::update()
{
	

}

void Renderer2D::draw(AppWindow* target)
{
}
