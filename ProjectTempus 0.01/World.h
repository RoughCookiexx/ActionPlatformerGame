#ifndef WORLD_H
#define WORLD_H
#pragma once 

#include <Box2D\Box2D.h>
#include "AnimatedSprite.h"
#include "ContactListener.h"
#include "Projectile.h"

class World
{
	private:
		b2World *world;
		ContactListener *contactListener;

		void loadTestLevel();
		float xOffset;
		float yOffset;

	public:
		World();
		void init();
		void update();
		void loadLevelFromFile();

		b2World* getB2World() { return world; }
		ContactListener* getContactListener() { return contactListener; }
		float getXOffset() { return xOffset; } 
		float getYOffset() { return yOffset; } 

		void setXOffset( float offset ) { xOffset = offset; }
		void setYOffset( float offset ) { yOffset = offset; }


};


#endif 