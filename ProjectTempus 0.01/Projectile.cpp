#include "Projectile.h"
#include <math.h>
#include "Physics.h"
#include "World.h"
#include "AssetManager.h"

#pragma once

Projectile::Projectile(AnimatedSprite *sprite, AnimatedSprite* owner, b2Vec2 offset, float velocity) 
{
	this->owner = owner;
	this->offset = offset;
	this->sprite = sprite;
	this->velocity = velocity;
	canFire = true;
	
	b2Body *body = sprite->getBody();
	body->SetBullet(true);
	body->SetActive(false);
	body->SetGravityScale(0);
	
	Physics::setFilterData(body, 0x0002, 0x0004, 0x0000);
}

bool Projectile::Fire(b2Vec2 targetPoint)
{
	if(canFire)
	{
		b2Body* body = sprite->getBody();
		body->SetActive(true);

		World *world = AssetManager::getAssetManager()->getWorld();

		b2Vec2 position = owner->getBody()->GetPosition();
		
		targetPoint.x += offset.x;
		targetPoint.x += world->getXOffset();
		targetPoint.x /=SCALE;
		targetPoint.y += offset.y;
		targetPoint.y += world->getYOffset();
		targetPoint.y /=SCALE;

	//Use Math.atan2(dy, dx) to find the angle. Then use cos and sin to set the velocity.
		float deltaX = targetPoint.x-position.x;
		float deltaY = targetPoint.y-position.y;
		float angle = atan2(deltaY, deltaX);
		float velocityX = cos(angle) * velocity;
		float velocityY = sin(angle) * velocity;
		

		body->SetLinearVelocity(b2Vec2(velocityX,velocityY));
		body->SetTransform(position, 0);

		return true;
	}
	else return false;
}