#include "Enemy.h"

Enemy::Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	:Sprite2D(model, shader, texture)
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(GLfloat deltatime)
{
}

void Enemy::Detect(std::shared_ptr<Player> player)
{
}
