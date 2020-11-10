#include "Player.h"


Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_isInAir = false;
	m_xSpeed = 150;
	m_ySpeed = -100;
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

	texture = ResourceManagers::GetInstance()->GetTexture("player_jump_up");
	m_pJumpUp = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 0.1f);
	m_pJumpUp->SetSize(52, 52);

	texture = ResourceManagers::GetInstance()->GetTexture("player_jump_down");
	m_pJumpDown = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 0.1f);
	m_pJumpDown->SetSize(52, 52);

	texture = ResourceManagers::GetInstance()->GetTexture("player_jump_letf_up");
	m_pJumpLeftUp = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 0.1f);
	m_pJumpLeftUp->SetSize(52, 52);

	texture = ResourceManagers::GetInstance()->GetTexture("player_jump_left_down");
	m_pJumpLeftDown = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 0.1f);
	m_pJumpLeftDown->SetSize(52, 52);

	m_pAnimation = m_pIdle;

	m_vPosition.x = 240;

	m_vPosition.y = 0;
}


Player::~Player()
{
	m_pAnimation = NULL;
	m_pRun = NULL;
}


void Player::HandleKeyEvents(GLbyte key, bool bIsPressed)
{
	if (!bIsPressed) {
		xSpeed = 0;
	}
	else {
		switch (key) {
		case KEY_SPACE:
			if (!m_isInAir)
			{
				m_isInAir = true;
				m_ySpeed = -300;
				
			}
			break;
		case KEY_RIGHT:
			m_isRight = true;
			xSpeed = -m_xSpeed;
			break;
		case KEY_LEFT:
			m_isRight = false;
			xSpeed = m_xSpeed;
			break;
		}
	}	
}

//void Player::Jump()
//{
//	if (m_isRight) {
//		m_pAnimation = m_pJumpUp;
//	}
//	else
//		m_pAnimation = m_pJumpLeftUp;
//}

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

void Player::CheckFlatform(std::shared_ptr<Flatform> flatform) {

	Vector2 pos = GetAnimation()->Get2DPosition();
	Vector2 fPos = flatform->Get2DPosition();
	Vector2 fSize = flatform->GetSize();

	
	if((pos.y + 26 <= fPos.y - fSize.y * 0.5 + 11) && (pos.y + 26 >= fPos.y - fSize.y * 0.5) && (pos.x + 10 >= fPos.x - fSize.x * 0.5 && pos.x - 10 <= fPos.x + fSize.x * 0.5))
	{
		m_vPosition.y = fPos.y - 0.5*fSize.y - 26;

		m_isInAir = false;
	}
	else m_isInAir = true;
}

void Player::Move(GLfloat deltatime)
{
	if (m_ySpeed > 0) {
		if (m_isRight)
			m_pAnimation = m_pJumpDown;
		else
			m_pAnimation = m_pJumpLeftDown;
	}
	else {
		if (m_isRight) {
			m_pAnimation = m_pJumpUp;
		}
		else
			m_pAnimation = m_pJumpLeftUp;
	}

	if (m_isInAir) {
		m_ySpeed += g;
	}
	else {
		m_ySpeed = 0;

		if (xSpeed == 0) {
			Idle();
		}
		else {
			Run();
		}
	}

	m_vPosition.y += m_ySpeed * deltatime;
	
	
}


void Player::Update(GLfloat deltatime)
{	
	Move(deltatime);
	m_pAnimation->Set2DPosition(m_vPosition);
}


