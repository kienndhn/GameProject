#pragma once 
#include "Sprite2D.h"
#include "ResourceManagers.h"
#include "SpriteAnimation.h";

class Player : public Sprite2D
{



public:
	Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Player();
	void	SetOnClick(void(*pBtClick)());
	void	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	bool	IsHandle();
	void	Run();
	std::shared_ptr<SpriteAnimation> GetAnimation() {
		return m_pAnimation;
	}

private:
	void(*m_pBtClick)();
	bool	m_isHandle;
	std::shared_ptr<SpriteAnimation> m_pAnimation;

};
