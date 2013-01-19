#pragma once

#include "SFML\Graphics\Sprite.hpp"
#include <Box2D\Box2D.h>
#include "CHRTimer.h"

enum SpriteType { PLAYER, BADGUY, NEUTRAL, GOOD_BULLET, BAD_BULLET };
enum Facing { LEFT, RIGHT };

// Some data necessary to work with a sprite sheet:
struct SpriteSheetData{
	int numOfActions, drawHeight, drawWidth;
	int* framesInAction;
	SpriteType type;
	float timeBetweenFrames;
};

// An extension of a sf::Sprite.
// This will make it easy to animate sprites using sprite sheets
// It also ties graphics together with physics.
class AnimatedSprite : public sf::Sprite
{
	

private:
	CHRTimer* timer;
	float timeSinceLastFrame;
	int currentActionNumber, currentFrameNumber; // What frame are we on
	b2Body* body; // Physical location of the texture
	b2Fixture* footSensor;
	int numFootContacts;
	Facing facing;
	int health;
	
	void nextFrame();

public:
	SpriteSheetData spriteSheetData; 

	AnimatedSprite(SpriteSheetData data, sf::Texture &texture, b2Body *initBody);
	void setAction(int actionNumber);
	void setFacing(Facing initFacing) {facing=initFacing;}
	void setFootSensor(b2Fixture *sensor) { footSensor = sensor; }
	void update();
	Facing getFacing() {return facing;}
	b2Fixture* getFootSensor() { return footSensor; }
	b2Body* getBody() { return body; }

};