#include "Player.h"


Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	
	
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("player_idle");
	m_pIdle = std::make_shared<SpriteAnimation>(model, shader, texture, 4, 0.1f);
	m_pIdle->SetSize(52, 52);
	texture = ResourceManagers::GetInstance()->GetTexture("player_run");
	m_pRun = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	m_pRun->SetSize(52, 52);
	m_pAnimation = m_pIdle;
	m_pAnimation->Set2DPosition(120, 120);
}

Player::~Player()
{
}


void Player::HandleKeyEvents(GLbyte key, bool bIsPressed)
{
	if (!bIsPressed) {
		Idle();
	}
	else {
		switch(key){
		case KEY_RIGHT:
			Run();
			break;
		}
			
	}
}


void Player::Run() {
	m_pAnimation = m_pRun;
	
}

void Player::Idle() {
	m_pAnimation = m_pIdle;
}

void Player::Update(GLfloat deltatime)
{
	m_pAnimation->Set2DPosition(120, 120);
}
