#include "Frog.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight;
extern int xSpeed;


Frog::Frog(std::shared_ptr<Models> model, GLint x, GLint y)
{
	m_xDistance = 1000;
	m_xSpeed = 150;
	m_ySpeed = 100;
	m_isActive = false;
	m_isAlive = true;
	m_isInAir = true;
	m_timeToDraw = 0;
	m_iScore = 25;
	m_timeToIdle = 2;
	m_isJumping = false;

	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("frog_idle");
	m_pIdle = std::make_shared<SpriteAnimation>(model, shader, texture, 4, 0.1f);
	m_pIdle->SetSize(42, 32);

	texture = ResourceManagers::GetInstance()->GetTexture("frog_up");
	m_pUp = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 0.1f);
	m_pUp->SetSize(42, 39);

	texture = ResourceManagers::GetInstance()->GetTexture("frog_down");
	m_pDown = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 0.1f);
	m_pDown->SetSize(42, 39);

	texture = ResourceManagers::GetInstance()->GetTexture("death");
	m_pDeath = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	m_pDeath->SetSize(54, 42);

	m_pAnimation = m_pIdle;
	m_pAnimation->Set2DPosition(x, y);
}

Frog::~Frog()
{
}

void Frog::Update(GLfloat deltatime)
{
	
	m_vPosition = GetAnimation()->Get2DPosition();

	if (m_vPosition.x - 39 < screenWidth && m_vPosition.x + 39 > 0)
	{
		m_isActive = true;
	}
	else
	{
		m_isActive = false;
	}

	if (m_vPosition.y - 21 > screenHeight) {
				m_isActive = false;
	}

	if (m_isAlive)
	{
		Move(deltatime);
	}
	else
	{
		m_vPosition.x += deltatime * xSpeed;
		m_pAnimation = m_pDeath;
		m_timeToDraw += deltatime;
	}

	GetAnimation()->Set2DPosition(m_vPosition);

	GetAnimation()->Update(deltatime);
}


void Frog::CheckFlatform(std::shared_ptr<Flatform> flatform)
{
	Vector2 pos = GetAnimation()->Get2DPosition();
	Vector2 fPos = flatform->Get2DPosition();
	Vector2 fSize = flatform->GetSize();

	if ((pos.y + 16 <= fPos.y - fSize.y * 0.5 + 16)&&(pos.y + 16 >= fPos.y - fSize.y * 0.5) && abs(fPos.x - pos.x) < fSize.x * 0.5)
	{
		m_isInAir = false;
		m_vPosition.y = fPos.y - 0.5 * fSize.y - 16;
	}

	else
	{
		if(CheckJump())
		m_isInAir = true;
	}
	if (pos.y + 16 > screenHeight)
	{
		m_isAlive = false;
	}
	GetAnimation()->Set2DPosition(m_vPosition);
}

void Frog::Move(GLfloat deltatime)
{
	m_timeToIdle += deltatime;

	if (m_isActive) {

		if(m_timeToIdle < 1)
		{
			m_xSpeed = 0;
			m_pAnimation = m_pIdle;
		}
		else if(m_timeToIdle < 5)
		{
			if (m_isJumping == false)
			{
				m_isJumping = true;
				m_xSpeed = 200;
				m_ySpeed = -250;
				m_pAnimation = m_pUp;
				m_isInAir = true;
			}
		}
		else
		{
			m_isJumping = false;
			m_timeToIdle = 0;
			m_pAnimation = m_pIdle;
		}
		

		if (m_ySpeed > 0)
		{
			m_pAnimation = m_pDown;
		}
		
		m_vPosition.x = m_vPosition.x - deltatime * (m_xSpeed - xSpeed);

		if (m_isInAir) {
			if (m_ySpeed < 280)
			{
				m_ySpeed += gravity;
			}
		
		}
		else {
			m_xSpeed = 0;
			m_ySpeed = 0;
			m_pAnimation = m_pIdle;
		}
		m_vPosition.y += m_ySpeed * deltatime;
	}
	else {
		m_vPosition.x = m_vPosition.x + deltatime * xSpeed;
	}
}

void Frog::Detect(std::shared_ptr<Player> player)
{
	Vector2 playerPos = player->GetAnimation()->Get2DPosition();
	Vector2 oposumPos = GetAnimation()->Get2DPosition();

	m_xDistance = oposumPos.x - playerPos.x;

	if (m_xDistance != 0 && abs(playerPos.y - oposumPos.y) < 40) {
		m_Direction = m_xDistance / abs(m_xDistance);
	}
}