#pragma once

#include "AnimatedSprite.h"
#include "Tokenizer.h"
#include <map>


struct ItemInfo {
	std::map<string, string> sMap;
	std::map<string, int> iMap;
};

class DataLoader
{
public : 
	static std::vector<ItemInfo*> MapFileInfo(string fileName);
};