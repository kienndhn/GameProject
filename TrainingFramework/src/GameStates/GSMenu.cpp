#include "GSMenu.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern int xSpeed;

GSMenu::GSMenu()
{

}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	/*ResourceManagers::GetInstance()->PlaySounds("menu", true);*/

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("back");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	std::shared_ptr<Sprite2D> bg1 = std::make_shared<Sprite2D>(model, shader, texture);
	bg1->Set2DPosition(screenWidth / 2, screenHeight / 2);
	bg1->SetSize(screenWidth, screenHeight);
	m_listBackGround.push_back(bg1);
	
	texture = ResourceManagers::GetInstance()->GetTexture("button_play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 150);
	button->SetOnClick([]() {
		ResourceManagers::GetInstance()->PauseSounds("menu");
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
	});
	m_listButton.push_back(button);

	//info button
	texture = ResourceManagers::GetInstance()->GetTexture("button_info");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 210);
	button->SetOnClick([]() {
		//ResourceManagers::GetInstance()->PauseSounds("menu");
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Credit);
	});
	m_listButton.push_back(button);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 270);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("GAME");
	m_Text_gameName = std::make_shared<Text>(shader, font, "Jumping Fox", TEXT_COLOR::RED, 2.0);
	m_Text_gameName->Set2DPosition(Vector2(100, 100));
}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{

}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}

	
}

void GSMenu::Update(float deltaTime)
{
	/*for (auto bg : m_listBackGround) {
		Vector2 pos = bg->Get2DPosition();
		pos.x = pos.x - 100 * deltaTime;
		if (pos.x < -screenWidth / 2 + 10) {
			pos.x = screenWidth * 1.5;
		}
		bg->Set2DPosition(pos);
	}*/
	for (auto bg : m_listBackGround) {
		bg->Update(deltaTime);
	}

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	for (auto bg : m_listBackGround) {
		bg->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_gameName->Draw();
}
