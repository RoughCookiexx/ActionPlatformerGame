
#include "DataLoader.h"
#include <fstream>
#include "Tokenizer.h"


// This will read through a file. It takes each value and stored it to an ID in a map.
// It will try to convert each value to an int and store it in the int map.
// If an int cannot be made, it will simply store the string in the string map.
// Each line must have a different value with the template: "key: value"
// Each item must be separated by a white line in the file. 
// Each value is assumed to be an int or a string.
vector<ItemInfo*> DataLoader::MapFileInfo(string fileName)
{
	// This is what will store all of the info about each item in the file:
	std::vector<ItemInfo*> itemInfoList;
	
	// Open the file:
	ifstream fileToRead;
	fileToRead.open(fileName);

	// This is for separating keys and values. 
	Tokenizer *tokenizer = new Tokenizer();

	if (fileToRead.is_open()) {
		while (!fileToRead.eof()) {

			// Create the ItemInfo struct to be added to the list.
			ItemInfo *info = new ItemInfo();

			// Read the first line of the item:
			string line = "";
			getline(fileToRead, line);

			while(line != "") // If the line is blank, we are done reading this item.
			{
				// Create the key and value strings.
				string key = "";
				string value = "";

				// Split the string into its key and value (Right now assume it's correct.)
				std::vector<string> splitString = tokenizer->Split(line, ':');
				key = splitString.at(0);
				value = splitString.at(1);

				// Add the entry to the proper map:
				int iValue;
				try { // Try to convert it to an int and store it in the int map:
					iValue = stoi(value);
					info->iMap[key] = iValue;
				} catch (std::invalid_argument e)
				{ // If it can't be converted to an int, just store it as a string:
					info->sMap[key] = value;
				}

				// Get the next line:
				getline(fileToRead, line);
			}

			// Add this item to the item list:
			itemInfoList.push_back(info);
		}
	}
	// Clean up:
	fileToRead.close();
	delete tokenizer;

	return itemInfoList;
}
