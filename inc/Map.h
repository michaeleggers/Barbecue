#pragma once
#include <string>
#include "../inc/Tile.h"

class Map
{
public:
	void Load(std::string path);

	Tile map[200];
};

