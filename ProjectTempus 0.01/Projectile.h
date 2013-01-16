#include "AnimatedSprite.h"
#include <Box2D\Box2D.h>

#pragma once

class Projectile
{
	AnimatedSprite* owner;
	AnimatedSprite* sprite;
	b2Vec2 offset;
	bool canFire;
	float velocity;

public:
	Projectile();
	Projectile(AnimatedSprite* sprite, AnimatedSprite* owner, b2Vec2 offset, float velocity=50);
	bool Fire(b2Vec2 targetPoint);
	AnimatedSprite* getSprite() { return sprite; }
};
