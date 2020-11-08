#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "SpriteAnimation.h"
#include "Player.h"
#include "Opossum.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern int xspeed;
int yspeed;
std::shared_ptr<Sprite2D> bg1;

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
	
}


void GSPlay::Init()
{
	xspeed = 0;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("back");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	//BackGround
	
	std::shared_ptr<Sprite2D> bg = std::make_shared<Sprite2D>(model, shader, texture);
	bg->Set2DPosition(screenWidth * 0.5, screenHeight / 2);
	bg->SetSize(screenWidth * 2, screenHeight * 2);
	m_listBackGround.push_back(bg);
	
	bg = std::make_shared<Sprite2D>(model, shader, texture);
	bg->Set2DPosition(screenWidth * 2.5 *  - 1, screenHeight / 2);
	bg->SetSize(screenWidth * 2, screenHeight * 2);
	m_listBackGround.push_back(bg);
	
	bg1 = std::make_shared<Sprite2D>(model, shader, texture);
	bg1->Set2DPosition(screenWidth * 0.5f, screenHeight / 2);
	bg1->SetSize(screenWidth * 2, screenHeight * 2);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	//new Player
	//shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_Player = std::make_shared<Player>(model, shader, texture);
	

	//new Opossum
    std::shared_ptr<Opossum> m_Opossum = std::make_shared<Opossum>(model, shader, texture);
	m_Opossum->GetAnimation()->Set2DPosition(screenWidth * 1.5, screenHeight / 2);
	m_listOpossum.push_back(m_Opossum);

	m_Opossum = std::make_shared<Opossum>(model, shader, texture);
	m_Opossum->GetAnimation()->Set2DPosition(screenWidth * 2.0, screenHeight / 2);
	m_listOpossum.push_back(m_Opossum);

	//ground
	
	shader= shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("ground");
	std::shared_ptr<Ground> m_Ground = std::make_shared<Ground>(model,shader, texture);
	m_Ground->Set2DPosition(screenWidth/2, 280);
	m_Ground->SetSize(336, 80);
	m_listGround.push_back(m_Ground);

	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(450, 25);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	m_Player->HandleKeyEvents(key, bIsPressed);
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
	printf("click");
}

void GSPlay::Update(float deltaTime)
{
	for (auto gr : m_listGround) {
		
		gr->Update(deltaTime);

	}

	bg1->Update(deltaTime);

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	m_Player->Update(deltaTime);

	

	for (auto bg : m_listBackGround) {
		Vector2 pos = bg->Get2DPosition();
		pos.x = pos.x + xspeed * deltaTime;
		
		if (pos.x < -screenWidth *1.5) {
			pos.x = screenWidth * 2.5;
			printf("reset\n");
		}
		else if (pos.x > screenWidth * 2.5) {
			pos.x = -screenWidth * -1.5;
			printf("reset\n");
		}
		bg->Set2DPosition(pos);
	}
	m_Player->GetAnimation()->Update(deltaTime);
	for (auto opossum : m_listOpossum) {
		
			opossum->GetAnimation()->Update(deltaTime);
			opossum->Detect(m_Player);
			opossum->Update(deltaTime);
		
		
	}
	
	
}

void GSPlay::Draw()
{
	
	bg1->Draw();

	for (auto obj : m_listBackGround)
	{
		obj->Draw();
	}

	m_Player->GetAnimation()->Draw();

	for (auto opossum : m_listOpossum) {
		opossum->GetAnimation()->Draw();
	}

	for (auto obj : m_listButton)
	{
		obj->Draw();
	}
	for (auto gr : m_listGround) {

		gr->Draw();

	}
	m_score->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}