#include "Sprite2D.h"
#include "ResourceManagers.h"
#include "SpriteAnimation.h";

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
	void Update(GLfloat deltatime);
	
private:
	std::shared_ptr<SpriteAnimation> m_pAnimation;
	int m_xSpeed;
	bool m_isActive;
};
