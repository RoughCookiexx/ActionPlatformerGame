#include "Graphics.h"
#include "AssetManager.h"

#define CAMERA_LIMIT_L 400
#define CAMERA_LIMIT_R 500
#define CAMERA_LIMIT_T 200
#define CAMERA_LIMIT_B 400

Graphics::Graphics()
{
}


void Graphics::init(World *world)
{
	// Create a window
	window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "SFML");

	// Create a Sprite Manager
	spriteManager = new SpriteManager();
	spriteManager->init(world->getB2World());

	// Setup debug drawing. Does this really belong here? probably not.
	//DebugDraw *draw = new DebugDraw(world);
	//draw->SetFlags(b2Draw::e_shapeBit);
	//world->getB2World()->SetDebugDraw(draw);
}

void Graphics::update(World *world)
{
	sf::Event event;   

	// HANDLE WINDOW EVENTS:
	while (window->pollEvent(event))
    {
            if (event.type == sf::Event::Closed)
                window->close();
	}

	// EXIT THE PROGRAM WHEN THE WINDOW IS CLOSED:
	if(!window->isOpen()) exit(0);

	// CLEAR THE PREVIOUS FRAME
	window->clear(sf::Color(100,100,100));

		// DRAW EVERYTHING:
		world->drawWorld(window);
		spriteManager->drawSprites(window);
		// DISPLAY THE FRAME: 


		followPlayer(world);
		window->display();

		//window->clear();
}

// moves the camera to follow the player.
// Values do not compensate for scaling. 
void Graphics::followPlayer(World *world)
{
	b2Body *body = AssetManager::getAssetManager()->getPlayer()->getBody();

	float playerX = body->GetPosition().x * SCALE;
	float playerY = body->GetPosition().y * SCALE;

	float xOffset = world->getXOffset();
	float yOffset = world->getYOffset();

	float playerScreenPosX = playerX - xOffset;
	float playerScreenPosY = playerY - yOffset;



	// MOVE CAMERA RIGHT
	if( (playerScreenPosX) > CAMERA_LIMIT_R) 
		world->setXOffset(xOffset + (playerScreenPosX - CAMERA_LIMIT_R));
	
	// MOVE CAMERA LEFT
	if( (playerScreenPosX) < CAMERA_LIMIT_L) 
		world->setXOffset(xOffset - (CAMERA_LIMIT_L - playerScreenPosX));

	// MOVE CAMERA DOWN
	if( (playerScreenPosY) > CAMERA_LIMIT_B) 
		world->setYOffset(yOffset + (playerScreenPosY - CAMERA_LIMIT_B));
	
	// MOVE CAMERA UP
	if( (playerScreenPosY) < CAMERA_LIMIT_T) 
		world->setYOffset(yOffset - (CAMERA_LIMIT_T - playerScreenPosY));
}