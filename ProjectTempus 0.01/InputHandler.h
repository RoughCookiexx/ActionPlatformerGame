#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "AnimatedSprite.h"
#include "World.h"
#include "Graphics.h"


class InputHandler
{


public:

	InputHandler();
	void handleInput(World *world, Graphics *graphics);

};