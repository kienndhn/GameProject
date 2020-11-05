#include "Player.h"


Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_xSpeed = 100;
	m_isRight = true;
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("player_idle");
	m_pIdle = std::make_shared<SpriteAnimation>(model, shader, texture, 4, 0.1f);
	m_pIdle->SetSize(52, 52);
	texture = ResourceManagers::GetInstance()->GetTexture("player_idle_left");
	m_pIdleLeft = std::make_shared<SpriteAnimation>(model, shader, texture, 4, 0.1f);
	m_pIdleLeft->SetSize(52, 52);
	texture = ResourceManagers::GetInstance()->GetTexture("player_run");
	m_pRun = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	m_pRun->SetSize(52, 52);
	texture = ResourceManagers::GetInstance()->GetTexture("player_run_left");
	m_pRunLeft = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	m_pRunLeft->SetSize(52, 52);
	m_pAnimation = m_pIdle;
	
}

Player::~Player()
{
}


void Player::HandleKeyEvents(GLbyte key, bool bIsPressed)
{
	if (!bIsPressed) {
		Idle();
		xspeed = 0;
	}
	else {
		switch(key){
		case KEY_RIGHT:
			m_isRight = true;
			Run();
			xspeed = -m_xSpeed;
			break;
		case KEY_LEFT:	
			m_isRight = false;
			Run();
			xspeed = m_xSpeed;
			break;
		}
			
	}
}


void Player::Run() {
	if (m_isRight) {
		m_pAnimation = m_pRun;
	}
	else {
		m_pAnimation = m_pRunLeft;
	}
	
	
}

void Player::Idle() {
	if (m_isRight) {
		m_pAnimation = m_pIdle;
	}
	else {
		m_pAnimation = m_pIdleLeft;
	}
}

void Player::Update(GLfloat deltatime)
{	
	m_pAnimation->Set2DPosition(240, 240);
}
