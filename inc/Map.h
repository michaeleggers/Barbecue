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
    ~Map();

		TileType* map_;

		int width_;
		int height_;
	};
}

