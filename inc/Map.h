#pragma once
#include <string>

class Tile
{
	
};

class Map
{
public:
	void Load(std::string path);

	Tile map[200];
};

