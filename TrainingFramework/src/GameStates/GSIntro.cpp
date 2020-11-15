#include "GSIntro.h"


extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine


extern int screenHeight;
extern int screenWidth;
extern int xSpeed;
extern int score;
GSIntro::GSIntro()
{
	m_timeToDraw = 0;
	xSpeed = 100;
}

GSIntro::~GSIntro()
{
}

void GSIntro::Init()
{
	ResourceManagers::GetInstance()->PlaySounds("menu", true);

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("back");

	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_background->SetSize(screenWidth, screenHeight);


	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("GAME");
	m_text = std::make_shared<Text>(shader, font, "Jumping Fox", TEXT_COLOR::RED, 2.0);
	m_text->Set2DPosition(Vector2(100, 100));

	//m_score = std::make_shared<Text>(shader, font, "Score " + std::to_string(score), TEXT_COLOR::RED, 1.5);
	//m_score->Set2DPosition(Vector2(160, 160));

	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("player_run");
	m_animation = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1);
	m_animation->Set2DPosition(10, 182);
	m_animation->SetSize(52, 52);

	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("largeground");
	std::shared_ptr<Sprite2D> obj = std::make_shared<Sprite2D>(model, shader, texture);
	obj->SetSize(960, 112);
	obj->Set2DPosition(screenWidth * 0.5, 264);
	m_listSprite.push_back(obj);

	texture = ResourceManagers::GetInstance()->GetTexture("tree");
	obj = std::make_shared<Sprite2D>(model, shader, texture);
	obj->SetSize(105, 93);
	obj->Set2DPosition(100, 162);
	m_listSprite.push_back(obj);

	texture = ResourceManagers::GetInstance()->GetTexture("house");
	obj = std::make_shared<Sprite2D>(model, shader, texture);
	obj->SetSize(83, 108);
	obj->Set2DPosition(400, 154);
	m_listSprite.push_back(obj);
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
	Vector2 pos = m_animation->Get2DPosition();

	pos.x += xSpeed * deltaTime;
	m_animation->Set2DPosition(pos.x, pos.y);

	if (pos.x >= 400) 
	{
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
	}
	m_animation->Update(deltaTime);

	m_background->Update(deltaTime);

	m_timeToDraw += deltaTime;

	m_text->Update(deltaTime);

	for (auto obj : m_listSprite)
	{
		obj->Update(deltaTime);
	}
}

void GSIntro::Draw()
{
	m_background->Draw();
	m_text->Draw();
	for (auto obj : m_listSprite)
	{
		obj->Draw();
	}
	m_animation->Draw();
}
