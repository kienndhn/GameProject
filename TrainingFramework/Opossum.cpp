#include "Opossum.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight;
extern int xspeed;
Opossum::Opossum(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_xDistance = 1000;
	m_xSpeed = 100;
	m_isActive = false;
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("opossum");
	m_pLeft = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	m_pLeft->SetSize(54, 42);
	texture = ResourceManagers::GetInstance()->GetTexture("opossum_right");
	m_pRight = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	m_pRight->SetSize(54, 42);
	m_pAnimation = m_pLeft;
}

Opossum::~Opossum()
{
}

void Opossum::Update(GLfloat deltatime) {

	
	Vector2 pos = GetAnimation()->Get2DPosition();
	

	if (m_isActive) {
		pos.x = pos.x - deltatime * (m_xSpeed * m_Direction - xspeed);
	}
	else {
		pos.x = pos.x + deltatime * xspeed;
	}
	
	GetAnimation()->Set2DPosition(pos);
}

void Opossum::Detect(std::shared_ptr<Player> player)
{
	Vector2 playerPos = player->GetAnimation()->Get2DPosition();
	Vector2 oposumPos = GetAnimation()->Get2DPosition();

	m_xDistance = oposumPos.x - playerPos.x;

	if (m_xDistance != 0) {
		m_Direction = m_xDistance / abs(m_xDistance);
	}
	if (m_Direction >= 0) {
		m_pAnimation = m_pLeft;
	}
	else {
		m_pAnimation = m_pRight;
	}
	if (abs(m_xDistance) < screenWidth / 2) {
		m_isActive = true;
	}
	else {
		m_isActive = false;
	}

}
