#include "Opossum.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight;
extern int xspeed;
Opossum::Opossum(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_xSpeed = 100;
	m_isActive = false;
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("opossum");
	m_pAnimation = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	m_pAnimation->SetSize(54, 42);
}

Opossum::~Opossum()
{
}

void Opossum::Update(GLfloat deltatime) {

	
	Vector2 pos = GetAnimation()->Get2DPosition();
	if (pos.x < screenWidth && pos.x >= 0) {
		m_isActive = true;
	}
	if (pos.x < 0) {
		m_isActive = false;
	}
	if (m_isActive) {
		pos.x = pos.x - deltatime * (m_xSpeed - xspeed);
	}
	else {
		pos.x = pos.x + deltatime * xspeed;
	}
	
	GetAnimation()->Set2DPosition(pos);
}