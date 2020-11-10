#pragma once
#include "Sprite2D.h"
#include "ResourceManagers.h"
#include "Player.h"

class Player;
extern int xSpeed;
extern int screenWidth;

class Flatform :
	public Sprite2D
{
public:
	Flatform(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
		:Sprite2D(model, shader, texture) {};
	Flatform() = default;
	
	~Flatform();
	
	void	SetSize(GLint width, GLint height);
	
	Vector2	GetSize() {
		return m_Size;
	}
	
	void	Update(GLfloat deltatime);

	void	CheckInScreen();

	bool	GetIsInScreen() {
		return m_isInScreen;
	};
private:
	
	Vector2 m_Size;
	
	bool	m_isInScreen;
};

