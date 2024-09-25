#pragma once
#include "InputListener.h"
class Camera;

class PlayerController: InputListener
{
private:
	Camera* cam = nullptr;
};

