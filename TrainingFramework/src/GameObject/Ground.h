#pragma once
#include "Sprite2D.h"
#include "FlatForm.h"
#include "ResourceManagers.h"

extern int xSpeed;
extern int YSpeed;
extern int g;
class Ground :
	public Flatform
{
public:
	Ground(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
		:Flatform(model, shader, texture) {};
		
	~Ground();
	void checkPlayer(std::shared_ptr<Player> player);
};

