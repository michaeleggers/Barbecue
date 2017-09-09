#pragma once
#include "../inc/TileInterface.h"
#include "../inc/Map.h"

namespace bbq
{
	class Tile : public TileInterface
	{
	public:
		Tile(TileType type, int x, int y, bbq::Sprite* sprite, Map* map);
		~Tile();

		TileInterface* getLeft() override;
		TileInterface* getRight() override;
		TileInterface* getUp() override;
		TileInterface* getDown() override;

		bool moveLeft() override;
		bool moveRight() override;
		bool moveUp() override;
		bool moveDown() override;
	};
}

