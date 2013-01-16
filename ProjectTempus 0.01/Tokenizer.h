#pragma once

#include "stdafx.h"
#include <string>
#include <vector>

using namespace std;

class Tokenizer
{

public:
	Tokenizer();
	vector<string> Split(string str, char deliminator);
};