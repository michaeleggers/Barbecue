#include "..\inc\Tile.h"

namespace bbq
{

	Tile::Tile(TileType type, int x, int y, bbq::Sprite * sprite, Map* map) : TileInterface(type, x, y, sprite, map)
	{

	}

	Tile::~Tile()
	{
	}

	TileInterface * Tile::getLeft()
	{
		return nullptr;
	}

	TileInterface * Tile::getRight()
	{
		return nullptr;
	}

	TileInterface * Tile::getUp()
	{
		return nullptr;
	}

	TileInterface * Tile::getDown()
	{
		return nullptr;
	}

	bool Tile::moveLeft()
	{
		return false;
	}

	bool Tile::moveRight()
	{
		return false;
	}

	bool Tile::moveUp()
	{
		return false;
	}

	bool Tile::moveDown()
	{
		return false;
	}
}
