
#pragma once

#include "CHRTimer.h"
#include "Physics.h"
#include "World.h"
#include "Graphics.h"
#include "AnimatedSprite.h"
#include "AssetManager.h"
#include "InputHandler.h"
#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML/OpenGL.hpp>


using namespace std;

class Game
{
	private:
		bool exit;
		Physics *physics;
		World *world;
		Graphics *graphics;
		InputHandler *input;
		AssetManager *assetManager;
		float fps;
		CHRTimer* timer;

	public:
		Game();
		~Game();

		void MainLoop();
		void init();

		float xOffset;
		float yOffset;
};