#include "AssetManager.h"
#include "SFML\Graphics\Sprite.hpp"

#pragma once

class BackgroundTexture : public sf::Sprite
{
public: 
	BackgroundTexture(string filename, float scrollSpeed);
	void Update();
private: 
	float scrollSpeed;
};