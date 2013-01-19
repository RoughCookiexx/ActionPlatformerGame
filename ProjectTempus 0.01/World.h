#ifndef WORLD_H
#define WORLD_H
#pragma once 

#include <Box2D\Box2D.h>
#include "AnimatedSprite.h"
#include "ContactListener.h"
#include "Projectile.h"
#include "SFML\Graphics.hpp"
#include "Bot.h"

class BackgroundTexture;

class World
{
	private:
		b2World *world;
		ContactListener *contactListener;
		std::vector<BackgroundTexture*> backgroundTextures;
		std::vector<Bot*> bots;

		void loadTestLevel();
		float xOffset;
		float yOffset;

	public:
		World();
		void init();
		void update();
		void loadLevelFromFile();
		void addBackgroundTexture(BackgroundTexture *texture) { backgroundTextures.push_back(texture); }
		void addBot(Bot* bot) { bots.push_back(bot);}
		void drawWorld(sf::RenderWindow *window);

		b2World* getB2World() { return world; }
		ContactListener* getContactListener() { return contactListener; }
		float getXOffset() { return xOffset; } 
		float getYOffset() { return yOffset; } 

		void setXOffset( float offset ) { xOffset = offset; }
		void setYOffset( float offset ) { yOffset = offset; }


};


#endif 