#pragma once 
#include "Sprite2D.h"
#include "ResourceManagers.h"
#include "SpriteAnimation.h";

class Player : public Sprite2D
{



public:
	Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Player();

	void	HandleKeyEvents(GLbyte key, bool bIsPressed);
	void	Run();
	void	Idle();
	std::shared_ptr<SpriteAnimation> GetAnimation() {
		return m_pAnimation;
	}
	void Update(GLfloat deltatime);

	
	
private:

	void(*m_pKeyPreesed)();
	bool m_isKeyPressed;
	std::shared_ptr<SpriteAnimation> m_pAnimation;
	std::shared_ptr<SpriteAnimation> m_pRun;
	std::shared_ptr<SpriteAnimation> m_pIdle;
};

