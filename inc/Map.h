#pragma once
#include <string>

namespace bbq
{
	class Tile;
	class Map
	{
	public:
		void Load(std::string path);

		Tile* map;

		int width;
		int height;
	};
}

