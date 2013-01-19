
#pragma once

#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include "glut.h"
#include "SpriteManager.h"
#include "AnimatedSprite.h"
#include "TiledLayer.h"
#include <Box2D\Box2D.h>
#include "DebugDraw.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 1000


class Graphics 
{
	private:
		sf::RenderWindow *window;
		SpriteManager *spriteManager;
		TiledLayer *tiledLayer;

	public:
		Graphics();
		void init(World *world);
		void update(World *world);
		void followPlayer(World *world);
		sf::RenderWindow* getWindow() { return window; }

		SpriteManager* getSpriteManager() { return spriteManager; }
};