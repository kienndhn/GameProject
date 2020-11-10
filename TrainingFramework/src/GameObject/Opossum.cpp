#include "Opossum.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight;
extern int xSpeed;

Opossum::Opossum(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_xDistance = 1000;
	m_xSpeed = 100;
	m_isActive = false;
	m_isInAir = false;

	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("opossum");
	m_pLeft = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	m_pLeft->SetSize(54, 42);
	
	texture = ResourceManagers::GetInstance()->GetTexture("opossum_right");
	m_pRight = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	m_pRight->SetSize(54, 42);

	m_pAnimation = m_pLeft;
}Opossum::Opossum(std::shared_ptr<Models> model)
{
	m_xDistance = 1000;
	m_xSpeed = 100;
	m_ySpeed = 0;
	m_isActive = false;
	
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("opossum");
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
	Move(deltatime);
	GetAnimation()->Set2DPosition(m_vPosition);
}

void Opossum::Detect(std::shared_ptr<Player> player)
{
	Vector2 playerPos = player->GetAnimation()->Get2DPosition();
	Vector2 oposumPos = GetAnimation()->Get2DPosition();

	m_xDistance = oposumPos.x - playerPos.x;

	if (m_xDistance != 0) {
		m_Direction = m_xDistance / abs(m_xDistance);
	}
	
	if (abs(m_xDistance) - 27 < screenWidth / 2 ) {
		m_isActive = true;
	}
	else {
		m_isActive = false;
	}
	if (oposumPos.y - 21> screenHeight) {
		m_isActive = false;
	}
}

void Opossum::CheckFlatform(std::shared_ptr<Flatform> flatform)
{
	Vector2 pos = GetAnimation()->Get2DPosition();
	Vector2 fPos = flatform->Get2DPosition();
	Vector2 fSize = flatform->GetSize();

	if ((pos.y + 21 <= fPos.y - fSize.y * 0.5 + 11) && (pos.y + 21 >= fPos.y - fSize.y * 0.5) && (pos.x + 10 >= fPos.x - fSize.x * 0.5 && pos.x - 10 <= fPos.x + fSize.x * 0.5))
	{
		m_vPosition.y = fPos.y - 0.5 * fSize.y - 27;
		m_isInAir = false;
	}

	else m_isInAir = true;

}



void Opossum::Move(GLfloat deltatime)
{
	m_vPosition = GetAnimation()->Get2DPosition();
	if (m_Direction >= 0) {
		m_pAnimation = m_pLeft;
	}
	else {
		m_pAnimation = m_pRight;
	}

	if (m_isActive) {
		m_vPosition.x = m_vPosition.x - deltatime * (m_xSpeed * m_Direction - xSpeed);
		if (m_isInAir) {
			m_ySpeed += g;
			printf("roi ne \n");
		}
		else {
			m_ySpeed = 0;
		}
		m_vPosition.y += m_ySpeed * deltatime;
	}
	else {
		m_vPosition.x = m_vPosition.x + deltatime * xSpeed;
	}	
}
