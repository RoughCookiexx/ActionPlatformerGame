#include "stdafx.h"
#include "Game.h"
#include "AnimatedSprite.h"
#include "AssetManager.h"



Game::Game()
{
	exit = false;
	xOffset = 0;
	yOffset = 0;
	fps = 30;
	timer = new CHRTimer();
}

void Game::init()
{
	graphics = new Graphics();
	world = new World();
	physics = new Physics();
	input = new InputHandler();


	graphics->init(world);
	world->init();
	physics->init();	

}

void Game::MainLoop()
{
	float frameStart = 0;
	float frameEnd = 0;

	while(!exit)
	{
		// Start our timer 
		// NOTE: can I make fps variable for slower systems?
		timer->Start();
		frameStart = (float)timer->GetElapsed();

		// The main calculations of the game: 
		//*****************************************************************
		input->handleInput(world, graphics);
		physics->update(world);  
		world->update();
		graphics->update(world);
		//*****************************************************************

		// This part simply holds the program until enough time has passed.
		//*****************************************************************
		do{
			timer->Stop();
			frameEnd += timer->GetElapsed();
			timer->Start();
		} while(frameEnd - frameStart  < (1/fps)*1000000);
		frameEnd = 0; // Reset the timer.
		//*****************************************************************
	}
}