#pragma once
#include <string>

namespace bbq
{
	class Tile;
	enum TileType;
	class Map
	{
	public:
		void Load(std::string path);

		TileType* map;

		int width;
		int height;
	};
}

