#include "Tokenizer.h"

Tokenizer::Tokenizer()
{

}

// Break apart a string using a specific character
vector<string> Tokenizer::Split(string str, char deliminator)
{
	vector<string> splitString;
	int nextDelimIndex = 0;
	int lastDelimIndex = 0;
	nextDelimIndex = str.find(deliminator);
	while(nextDelimIndex != string::npos)
	{
		splitString.push_back(str.substr(lastDelimIndex, nextDelimIndex-lastDelimIndex));
		lastDelimIndex = ++nextDelimIndex;
		nextDelimIndex = str.find(deliminator, lastDelimIndex);
	}
	splitString.push_back(str.substr(lastDelimIndex, str.length()-lastDelimIndex));

	return splitString;
}