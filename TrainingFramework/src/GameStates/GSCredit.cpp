#include "GSCredit.h"

extern int screenHeight;
extern int screenWidth;

GSCredit::GSCredit()
{
}

GSCredit::~GSCredit()
{
}

void GSCredit::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("credit");

	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_background->SetSize(screenWidth, screenHeight);

	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	m_button = std::make_shared<GameButton>(model, shader, texture);
	m_button->Set2DPosition(450, 25);
	m_button->SetOnClick([]()
	{
		//ResourceManagers::GetInstance()->PlaySounds("menu", true);
		GameStateMachine::GetInstance()->PopState();
	});
	
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("GAME");
	m_text = std::make_shared<Text>(shader, font, "made by Kien", TEXT_COLOR::RED, 2.0);
	m_text->Set2DPosition(Vector2(100, 100));
}

void GSCredit::Exit()
{
}

void GSCredit::Pause()
{
}

void GSCredit::Resume()
{
}

void GSCredit::HandleEvents()
{
}

void GSCredit::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSCredit::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_button->HandleTouchEvents(x, y, bIsPressed);
}

void GSCredit::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	m_button->Update(deltaTime);
	m_text->Update(deltaTime);
}

void GSCredit::Draw()
{
	m_background->Draw();
	m_button->Draw();
	m_text->Draw();
}

void GSCredit::Mute()
{
}

void GSCredit::Sound()
{
}
