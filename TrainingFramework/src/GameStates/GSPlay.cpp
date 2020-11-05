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

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern int speed;

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	speed = 0;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("back");

	//BackGround
	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	std::shared_ptr<Sprite2D> bg1 = std::make_shared<Sprite2D>(model, shader, texture);
	bg1->Set2DPosition(screenWidth / 2, screenHeight / 2);
	bg1->SetSize(screenWidth, screenHeight);
	m_listBackGround.push_back(bg1);
	std::shared_ptr<Sprite2D> bg2 = std::make_shared<Sprite2D>(model, shader, texture);
	bg2->Set2DPosition(screenWidth * 1.5 - 1, screenHeight / 2);
	bg2->SetSize(screenWidth, screenHeight);
	m_listBackGround.push_back(bg2);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	//new Player
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_Player = std::make_shared<Player>(model, shader, texture);
	

	// Animation
	/*shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("player_run");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	obj->Set2DPosition(120, 120);
	obj->SetSize(52, 52);
	m_listSpriteAnimations.push_back(obj);
*/

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

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	m_Player->Update(deltaTime);

	for (auto bg : m_listBackGround) {
		Vector2 pos = bg->Get2DPosition();
		pos.x = pos.x + speed * deltaTime;
		
		if (pos.x < -screenWidth / 2 + 1) {
			pos.x = screenWidth * 1.5 - 1;
			printf("reset\n");
		}
		else if (pos.x > screenWidth * 1.5 - 1 ) {
			pos.x = -screenWidth * 0.5 + 1;
			printf("reset\n");
		}
		bg->Set2DPosition(pos);
	}

	m_Player->GetAnimation()->Update(deltaTime);

}

void GSPlay::Draw()
{
	
	for (auto obj : m_listBackGround)
	{
		obj->Draw();
	}

	m_Player->GetAnimation()->Draw();

	for (auto obj : m_listButton)
	{
		obj->Draw();
	}

	m_score->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}