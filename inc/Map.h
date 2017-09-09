#pragma once
#include <string>
#include "../inc/Tile.h"

namespace bbq
{
	class Map
	{
	public:
		void Load(std::string path);

		Tile* map;

		int width;
		int height;
	};
}

