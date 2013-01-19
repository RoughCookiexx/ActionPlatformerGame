
#include "World.h"
#include "AnimatedSprite.h"
#include "SpriteManager.h"
#include "Projectile.h"

#pragma once

class AssetManager
{
private: 
	SpriteManager* spriteManager;
	AnimatedSprite* player;
	Projectile* timeBullet;
	World* world;


public:
	static AssetManager *assetManager;
	AssetManager();
	static AssetManager* getAssetManager();
	AnimatedSprite* getPlayer() { return player; }
	Projectile* getTimeBullet() { return timeBullet; }
	SpriteManager* getSpriteManager() { return spriteManager; }
	World* getWorld() { return world; }

	void setPlayer(AnimatedSprite* player) { this->player = player; } 
	void setSpriteManager(SpriteManager* initspriteManager) { spriteManager = initspriteManager; }
	void setTimeBullet(Projectile* initTimeBullet) { timeBullet = initTimeBullet; }
	void setWorld(World* initWorld) { world = initWorld; }

};