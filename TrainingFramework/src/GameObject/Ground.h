#pragma once
#include "Sprite2D.h"
#include "ResourceManagers.h"

class Ground :
	public Sprite2D
{
public:
	Ground(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
		:Sprite2D(model, shader, texture) {};
	~Ground();
};

