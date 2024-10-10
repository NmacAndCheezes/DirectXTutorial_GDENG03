#include "Renderer.h"
#include "RenderSystem.h"
#include "GraphicsEngine.h"

Renderer::Renderer(AGameObject* obj, void* shader_byte_code, size_t size_shader) : Component(obj)
{
	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

void Renderer::draw(AppWindow* target)
{
}
