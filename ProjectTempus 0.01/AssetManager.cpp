#include "AssetManager.h"

AssetManager* AssetManager::assetManager = NULL;


AssetManager::AssetManager() 
{
	player = NULL;
	timeBullet = NULL;
	spriteManager = NULL;
}


AssetManager* AssetManager::getAssetManager()
	{
		if(assetManager == NULL)
			AssetManager::assetManager = new AssetManager();
		return AssetManager::assetManager;
	}