#include "GSIntro.h"


extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine


GSIntro::GSIntro()
{
	m_timeToDraw = 0;
}


GSIntro::~GSIntro()
{	
}


void GSIntro::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("back");

	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_background->SetSize(screenWidth, screenHeight);

	texture = ResourceManagers::GetInstance()->GetTexture("demo");
	m_logo = std::make_shared<Sprite2D>(model, shader, texture);
	m_logo->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_logo->SetSize(60, 60);
}

void GSIntro::Exit()
{
	
}


void GSIntro::Pause()
{
	
}

void GSIntro::Resume()
{
	
}


void GSIntro::HandleEvents()
{
	
}

void GSIntro::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSIntro::HandleTouchEvents(int x, int y, bool bIsPressed)
{

}

void GSIntro::Update(float deltaTime)
{
	m_timeToDraw += deltaTime;
	if (m_timeToDraw > 1.3)
	{
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		m_timeToDraw = 0;
	}
}

void GSIntro::Draw()
{
	m_background->Draw();
	m_logo->Draw();
}
