#pragma once

#include "SFML\Graphics\Sprite.hpp"
#include <Box2D\Box2D.h>
#include "CHRTimer.h"
#include <time.h>

enum SpriteType {
    PLAYER =        0x0001,
    BADGUY =		0x0002,
    NEUTRAL =       0x0004,
    GOOD_BULLET =	0x0008,
    BAD_BULLET =    0x0010,
	LEVEL =			0X0011
  };

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
	CHRTimer* timer; // Timer for animation
	float timeSinceLastFrame; // Time since the last frame was displayed.
	int currentActionNumber, currentFrameNumber; // What frame are we on
	b2Body* body; // Physical location of the texture
	Facing facing; // Facing left or right
	int health; // How far from dead

	// Jump stuff:
	b2Fixture* footSensor; 
	int numFootContacts;
	float jumpTimer;
	
	void nextFrame(); // Play next frame

public:
	SpriteSheetData spriteSheetData; // *** WHY IS THIS PUBLIC? *** 

	AnimatedSprite(SpriteSheetData data, sf::Texture &texture, b2Body *initBody);
	void setAction(int actionNumber);
	void setFacing(Facing initFacing) {facing=initFacing;}
	void setFootSensor(b2Fixture *sensor) { footSensor = sensor; }
	void update();
	void startJumpTimer() { jumpTimer = (float)clock(); }
	int getNumFootContacts() { return numFootContacts; }

	Facing getFacing() {return facing;}
	b2Fixture* getFootSensor() { return footSensor; }
	float getJumpTime() {return jumpTimer; }
	b2Body* getBody() { return body; }
	SpriteType getSpriteType() { return spriteSheetData.type; }

	void hurt();
	void kill();
	

};