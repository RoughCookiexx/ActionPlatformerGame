#include "BackgroundTexture.h"

BackgroundTexture::BackgroundTexture(string fileName, float scrollSpeed)
{
	sf::Texture *texture = new sf::Texture();
			texture->loadFromFile(fileName);
	this->setTexture(*texture);
			this->scrollSpeed = scrollSpeed;
}

void BackgroundTexture::Update()
{
	World* world = AssetManager::getAssetManager()->getWorld();

	// Cast to a transformable just to move it.
	sf::Transformable* image = (sf::Transformable*)this;
	float x = (-1* world->getXOffset() ) * scrollSpeed;
	float y = (-1* world->getYOffset() ) * scrollSpeed;

	image->setPosition(x, y);
}