#include "AnimatedSprite.h"
#include "SFML\Graphics\Sprite.hpp"
#include "Physics.h"
#include "AssetManager.h"


AnimatedSprite::AnimatedSprite(SpriteSheetData data, sf::Texture &texture, b2Body *initBody) : Sprite(texture)
{
	body = initBody; 
	spriteSheetData = data;
	currentActionNumber = 0;
	currentFrameNumber = 0;
	sf::IntRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.height = data.drawHeight;
	rect.width = data.drawWidth;
	facing = RIGHT; // for now always start looking to the right.

	// This is to check if the sprite is touching a ground body. For jumping.
	numFootContacts = 0;
	jumpTimer = 0;

	// This is for timing the swapping of frames. 
	timer = new CHRTimer();
	timeSinceLastFrame = 0;

	// How much health we start with.
	health = 100;

	// Texture stuff: 
	this->setTexture(texture);
	this->setTextureRect(rect);
}

void AnimatedSprite::nextFrame()
{
	sf::IntRect rect= this->getTextureRect();

	currentFrameNumber++;
	currentFrameNumber %= spriteSheetData.framesInAction[currentActionNumber];

	if(currentFrameNumber == 0)
		rect.left = 0;
	else
		rect.left = currentFrameNumber * rect.width;

	this->setTextureRect(rect);
}

// Called once every frame of the game. 
void AnimatedSprite::update()
{
	World* world = AssetManager::getAssetManager()->getWorld();

	// Update the position of the sprite:
	float x = body->GetPosition().x  * SCALE - (spriteSheetData.drawWidth / 2)  - world->getXOffset();
	float y = body->GetPosition().y  * SCALE - (spriteSheetData.drawHeight / 2) - world->getYOffset();

	if(this->getScale().x == -1)
		x += getTextureRect().width;

	this->setPosition(x, y);

	// Stop the timer 
	timer->Stop();
	timeSinceLastFrame += timer->GetElapsedAsSeconds();

	// When the timer reaches the right amount of time, switch frames.
	if(timeSinceLastFrame  > spriteSheetData.timeBetweenFrames  )
	{
		nextFrame();
		timeSinceLastFrame = 0;
	}
	timer->Start();

}

// This changes the action number. 
void AnimatedSprite::setAction(int actionNumber)
{
	this->currentActionNumber = actionNumber;
	sf::IntRect rect= this->getTextureRect();
	rect.top = rect.height * actionNumber;
	this->setTextureRect(rect);
}

void AnimatedSprite::kill()
{
	this->getBody()->SetLinearVelocity(b2Vec2(1000,-100));
}

void AnimatedSprite::hurt()
{
	health -= 20;
	if(health <= 0)
		kill();
}