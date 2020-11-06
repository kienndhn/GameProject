#include "Sprite2D.h"
#include "ResourceManagers.h"
#include "SpriteAnimation.h";
#include "Player.h"
//#include "Enemy.h"
#include <math.h>

extern int speed;

class Opossum : public Sprite2D
{

public:
	Opossum(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Opossum();
	int GetXSpeed() {
		return m_xSpeed;
	}
	
	std::shared_ptr<SpriteAnimation> GetAnimation() {
		return m_pAnimation;
	}

	bool GetAcvite(){
		return m_isActive;
	}
	void Update(GLfloat deltatime);
	
	void Detect(std::shared_ptr<Player> player);
private:

	std::shared_ptr<SpriteAnimation> m_pAnimation;
	std::shared_ptr<SpriteAnimation> m_pLeft;
	std::shared_ptr<SpriteAnimation> m_pRight;
	int m_xSpeed;

	bool m_isActive;

	int m_xDistance;
	int m_Direction;
};
