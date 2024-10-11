#include "Renderer.h"
#include "Vector3D.h"
#include "Prerequisites.h"

class Renderer2D : public Renderer
{
public:
	Renderer2D(AGameObject* obj);
	virtual void update() override;
	virtual void draw(AppWindow* target) override;
	~Renderer2D() {}
};