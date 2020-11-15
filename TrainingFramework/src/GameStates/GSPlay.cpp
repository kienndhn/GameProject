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
#include "Item.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern int xSpeed;
extern int ySpeed;
extern int score;

std::shared_ptr<Sprite2D> bg1;

GSPlay::GSPlay()
{
	m_isPause = false;
	m_isPass = false;
}


GSPlay::~GSPlay()
{
	ResourceManagers::GetInstance()->PauseSounds("play");
}


void GSPlay::Init()
{
	xSpeed = 0;
	score = 0;

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("back");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	
	//BackGround
	bg1 = std::make_shared<Sprite2D>(model, shader, texture);
	bg1->Set2DPosition(screenWidth * 0.5f, screenHeight / 2);
	bg1->SetSize(screenWidth , screenHeight);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("GAME");
	m_score = std::make_shared<Text>(shader, font, "score " + std::to_string(score), TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));
	

	//new Player
	m_Player = std::make_shared<Player>(model, shader, texture);
	

	//new Opossum
	SetOpossum(model);

	//ground
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	SetMap(model, shader);
	
	//item
	SetItem(model);


	//button
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(450, 25);
	button->SetOnClick([]() 
	{
		ResourceManagers::GetInstance()->PlaySounds("menu", true);
		GameStateMachine::GetInstance()->PopState();
	});

	m_listButton.push_back(button);
	texture = ResourceManagers::GetInstance()->GetTexture("button_play");button = std::make_shared<GameButton>(model, shader, texture);
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(400, 25);
	button->SetActive(false);
	button->SetOnClick([]()
	{
		GameStateMachine::GetInstance()->CurrentState()->Resume();
	});

	m_listButton.push_back(button);
	texture = ResourceManagers::GetInstance()->GetTexture("button_pause"); button = std::make_shared<GameButton>(model, shader, texture);
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(400, 25);
	button->SetOnClick([]()
	{
		GameStateMachine::GetInstance()->CurrentState()->Pause();
	});
	m_listButton.push_back(button);
	ResourceManagers::GetInstance()->PlaySounds("play", true);

	
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{
	m_isPause = true;
	m_listButton[1]->SetActive(true);
	m_listButton[2]->SetActive(false);
	ResourceManagers::GetInstance()->m_Soloud.setPauseAll(true);
}

void GSPlay::Resume()
{
	m_isPause = false;
	m_listButton[1]->SetActive(false);
	m_listButton[2]->SetActive(true);
	ResourceManagers::GetInstance()->m_Soloud.setPauseAll(false);
}


void GSPlay::HandleEvents()
{
	for (auto gr : m_listFlatform)
	{
		Vector2 pos = gr->Get2DPosition();
		if (gr->GetIsInScreen())
		{
			m_Player->CheckFlatform(gr);
			if (!m_Player->GetInAir())
			{
				break;
			}
		}
	}
	
	for (auto item : m_listItem) {
		if (!item->ChechIsFed()) {
			
			m_Player->CheckItem(item);
		
		}
	}

	for (auto op : m_listOpossum) 
	{
		if (op->CheckAlive())
		{
			if (op->GetAcvite())
			{
				m_Player->CheckCollision(op);

				for (auto gr : m_listFlatform)
				{
					if (gr->GetIsInScreen())
					{
						op->CheckFlatform(gr);
						if (!op->GetInAir())
						{
							break;
						}
					}
				}
			}
		}
	}
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	m_Player->HandleKeyEvents(key, bIsPressed);
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		if (it->GetActive()) {
			(it)->HandleTouchEvents(x, y, bIsPressed);
			if ((it)->IsHandle()) break;
		}
	}
}

void GSPlay::Update(float deltaTime)
{
	if (CheckPass())
	{
		ResourceManagers::GetInstance()->PauseSounds("play");

		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Done);
	}
	if(!m_isPause)
	{
		m_score->setText("score " + std::to_string(score));

		m_Player->Update(deltaTime);

		if (m_Player->CheckAlive())
		{

			m_pHome->Update(deltaTime);

			for (auto gr : m_listFlatform)
			{
				gr->CheckInScreen();
				gr->Update(deltaTime);
			}

			bg1->Update(deltaTime);

			for (auto opossum : m_listOpossum)
			{
				if (opossum->GetTimeToDraw() < 0.5)
				{
					opossum->Detect(m_Player);
					opossum->Update(deltaTime);
				}
			}

			for (auto item : m_listItem)
			{
				if (item->GetTimeToDraw() < 0.5)
				{
					item->Update(deltaTime);
				}
			}
			HandleEvents();
		}

		else {

			ResourceManagers::GetInstance()->PauseSounds("play");

			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Finish);

		}
	}
	

	for (auto it : m_listButton)
	{
		if (it->GetActive())
		{
			it->Update(deltaTime);
		}
	}
	m_score->Update(deltaTime);
}

void GSPlay::Draw()
{

	bg1->Draw();

	for (auto gr : m_listFlatform)
	{
		gr->Draw();
	}

	for (auto opossum : m_listOpossum)
	{
		if (opossum->GetTimeToDraw() < 0.5)
		{
			opossum->GetAnimation()->Draw();
		}
	}

	for (auto item : m_listItem)
	{
		if (item->GetTimeToDraw() < 0.5)
		{
			item->GetAnimation()->Draw();
		}
	}

	m_pHome->Draw();

	m_Player->GetAnimation()->Draw();

	for (auto obj : m_listButton)
	{
		if (obj->GetActive())
		{
			obj->Draw();
		}
	}

	m_score->Draw();
}

bool GSPlay::CheckPass()
{
	Vector2 pPos = m_Player->GetAnimation()->Get2DPosition();
	Vector2 hPos = m_pHome->Get2DPosition();

	if (sqrt((pPos.x - hPos.x)*(pPos.x - hPos.x) + (pPos.y - hPos.y)*(pPos.y - hPos.y)) < 54) 
	{
		return true;
	}
	return false;

}

void GSPlay::SetMap(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader)
{

	auto texture = ResourceManagers::GetInstance()->GetTexture("house");
	m_pHome = std::make_shared<Home>(model, shader, texture, 2000, 154, 87, 108);


	texture = ResourceManagers::GetInstance()->GetTexture("ground");
	std::shared_ptr<Flatform> m_Ground = std::make_shared<Flatform>(model, shader, texture, 200, 280, 336, 80);
	m_listFlatform.push_back(m_Ground);

	m_Ground = std::make_shared<Flatform>(model, shader, texture, 3000, 280, 336, 80);
	m_listFlatform.push_back(m_Ground);

	texture = ResourceManagers::GetInstance()->GetTexture("largeground");
	m_Ground = std::make_shared<Flatform>(model, shader, texture, 960, 264, 960, 112);
	m_listFlatform.push_back(m_Ground);

	m_Ground = std::make_shared<Flatform>(model, shader, texture, 2000, 264, 960, 112);
	m_listFlatform.push_back(m_Ground);

	texture = ResourceManagers::GetInstance()->GetTexture("floater");
	m_Ground = std::make_shared<Flatform>(model, shader, texture, 2550, 150, 48, 16);
	m_listFlatform.push_back(m_Ground);

	m_Ground = std::make_shared<Flatform>(model, shader, texture, 2700, 150, 48, 16);
	m_listFlatform.push_back(m_Ground);

	m_Ground = std::make_shared<Flatform>(model, shader, texture,900, 150, 48, 16);
	m_listFlatform.push_back(m_Ground);

	m_Ground = std::make_shared<Flatform>(model, shader, texture, 3250, 180, 48, 16);
	m_listFlatform.push_back(m_Ground);

	texture = ResourceManagers::GetInstance()->GetTexture("smallfloater");
	m_Ground = std::make_shared<Flatform>(model, shader, texture, 3370, 170, 32, 16);
	m_listFlatform.push_back(m_Ground);
}

void GSPlay::SetOpossum(std::shared_ptr<Models> model) {
	std::shared_ptr <Opossum> m_Opossum = std::make_shared<Opossum>(model, screenWidth * 1.5, 150);
	m_listOpossum.push_back(m_Opossum);

	m_Opossum = std::make_shared<Opossum>(model, screenWidth * 2.0, 150);
	m_listOpossum.push_back(m_Opossum);
}

void GSPlay::SetItem(std::shared_ptr<Models> model)
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("gem");
	std::shared_ptr<Item> m_Gem = std::make_shared<Item>(model, texture, 300, 200, 20);
	m_listItem.push_back(m_Gem);
}
