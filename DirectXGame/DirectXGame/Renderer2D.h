#include "Renderer.h"
#include "Vector3D.h"
#include "Prerequisites.h"

class Renderer2D : public Renderer
{
public:
	Renderer2D(AGameObject* obj, void* shader_byte_code, size_t size_shader);
	virtual void update() override;
	virtual void draw(AppWindow* target) override;
	~Renderer2D() {}

protected:

	struct vertex
	{
		Vector3D position;
		Vector3D color;
		Vector3D color1;
	};


};