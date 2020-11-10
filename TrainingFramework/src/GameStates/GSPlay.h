#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "FlatForm.h"
#include "Ground.h"

class Sprite2D;
class Sprite3D;
class Text;
class SpriteAnimation;
class Player;
class Opossum;
class Ground;
class Platform;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	
	~GSPlay();

	void	Init();
	
	void	Exit();
	
	void	Pause();
	
	void	Resume();

	void	HandleEvents();
	
	void	HandleKeyEvents(int key, bool bIsPressed);

	void	HandleTouchEvents(int x, int y, bool bIsPressed);
	
	void	Update(float deltaTime);
	 
	void	Draw();

	
	void	SetNewPostionForBullet();

private:

	std::list<std::shared_ptr<Sprite2D>> m_listBackGround;
	
	std::shared_ptr<Text>  m_score;
	
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	
	std::vector < std::shared_ptr<SpriteAnimation>> m_listSpriteAnimations;
	
	std::vector < std::shared_ptr<Sprite2D>> m_listSprite2D;
	
	std::shared_ptr<Player> m_Player;
	
	std::list< std::shared_ptr<Opossum>> m_listOpossum;
	
	std::list<std::shared_ptr<Flatform>> m_listFlatform;
};


