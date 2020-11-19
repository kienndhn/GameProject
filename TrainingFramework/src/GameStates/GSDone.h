#pragma once
#include "GameStatebase.h"
#include "GameButton.h"
#include "SpriteAnimation.h"

class GSDone :
	public GameStateBase
{
public:
	GSDone();
	~GSDone();

	void	Init();
	void	Exit();

	void	Pause();
	void	Resume();

	void	HandleEvents();
	void	HandleKeyEvents(int key, bool bIsPressed);
	void	HandleTouchEvents(int x, int y, bool bIsPressed);
	void	Update(float deltaTime);
	void	Draw();

	void	HighScore();
	void	Mute();

	void	Sound();
private:
	std::list<std::shared_ptr<Sprite2D>> m_listSprite;
	std::list<std::shared_ptr<GameButton>> m_listButton;
	std::shared_ptr<Text> m_text;
	std::shared_ptr<Text> m_score;
	std::shared_ptr<Sprite2D> m_background;
	std::shared_ptr<SpriteAnimation> m_animation;
	std::shared_ptr<SpriteAnimation> m_animation1;
};

