#pragma once 
#include "Sprite2D.h"
#include "ResourceManagers.h"
#include "SpriteAnimation.h";
#include "FlatForm.h"
#include "Opossum.h"

class Flatform;
extern int xSpeed;
extern int g;

class Player : public Sprite2D
{

public:
	Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	
	~Player();

	void	HandleKeyEvents(GLbyte key, bool bIsPressed);
	
	void	Run();
	
	void	Idle();
	
	//void	Jump();
	
	void	Move(GLfloat deltatime);
	
	std::shared_ptr<SpriteAnimation> GetAnimation() {
		return m_pAnimation;
	}

	void Update(GLfloat deltatime);
	
	int GetxSpeed() {
		return m_xSpeed;
	}
	
	void CheckFlatform(std::shared_ptr<Flatform> flatform);
	
	bool GetInAir() {
		return m_isInAir;
	}

	void CheckCollision(std::shared_ptr<Opossum> opossum);

private:
	
	void(*m_pKeyPreesed)();
	
	bool m_isKeyPressed;
	
	bool m_isRight;
	
	bool m_isInAir;
	
	int m_xSpeed;
	
	int m_ySpeed;
	
	Vector2 m_vPosition;
	
	std::shared_ptr<SpriteAnimation> m_pAnimation;
	
	std::shared_ptr<SpriteAnimation> m_pRun;
	
	std::shared_ptr<SpriteAnimation> m_pIdle;
	
	std::shared_ptr<SpriteAnimation> m_pRunLeft;
	
	std::shared_ptr<SpriteAnimation> m_pIdleLeft;
	
	std::shared_ptr<SpriteAnimation> m_pJumpUp;

	std::shared_ptr<SpriteAnimation> m_pJumpDown;
	
	std::shared_ptr<SpriteAnimation> m_pJumpLeftUp;

	std::shared_ptr<SpriteAnimation> m_pJumpLeftDown;
};


