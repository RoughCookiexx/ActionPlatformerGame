#pragma once

#include "AnimatedSprite.h"
#include "SFML\Graphics.hpp"
#include "Tokenizer.h"
#include "physics.h"
#include <vector>

using namespace std;

class SpriteManager
{
private:
	Projectile *timeBullet;
	b2Body* groundBody;
	vector<AnimatedSprite*> badguySprites;
	vector<AnimatedSprite*> neutralSprites;
	AnimatedSprite *player;
	void createTimeBullet(b2World *world);
	void updateSprites();

public:
	SpriteManager();
	void init(b2World *world);
	void addSprite(AnimatedSprite* sprite);
	void drawSprites(sf::RenderWindow *window);
	void addSpritesFromFile(string fileString, b2World *world);
	
	b2Body* getGB() { return groundBody; }
	AnimatedSprite* getPlayer() { return player; }
};