#pragma once
#include "Sprite2D.h"
#include "FlatForm.h"
#include "ResourceManagers.h"

extern int xSpeed;
extern int YSpeed;
extern int g;
class Floater :
	public Flatform
{
public:
	Floater(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint x, GLint y, GLint width, GLint height)
		:Flatform(model, shader, texture, x, y, width, height) {};

	~Floater();
};