#pragma once
#include "Sprite2D.h"
#include "SpriteAnimation.h"
#include "Player.h"
class Enemy :
	public Sprite2D
{
public:
	Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Enemy();
	

	std::shared_ptr<SpriteAnimation> GetAnimation() {
		return m_pAnimation;
	}

	bool GetAcvite() {
		return m_isActive;
	}
	void Update(GLfloat deltatime);

	void Detect(std::shared_ptr<Player> player);
private:

	std::shared_ptr<SpriteAnimation> m_pAnimation;
	std::shared_ptr<SpriteAnimation> m_pLeft;
	std::shared_ptr<SpriteAnimation> m_pRight;
	int m_xSpeed;

	bool m_isActive;
};

