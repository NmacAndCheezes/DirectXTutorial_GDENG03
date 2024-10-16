#include "Component.h"
#include "Vector3D.h"
#include "Prerequisites.h"

class Renderer2D : public Component
{
public:
	Renderer2D(AGameObject* obj);
	virtual void update() override;
	virtual void release() override;
	~Renderer2D() {}

protected:
	VertexBufferPtr m_vb = nullptr;
	VertexShaderPtr m_vs = nullptr;
	PixelShaderPtr m_ps = nullptr;

	struct vertex
	{
		Vector3D position;
		Vector3D color;
		Vector3D color1;
	};


};