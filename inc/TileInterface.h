#pragma once

#include "../inc/Sprite.h"
#include "../inc/Map.h"
namespace bbq
{
	enum TileType
	{
		Player1,
		Player2,
		Free,
		Box1,
    Box2,
		Wall
	};

	class TileInterface
	{
	public:
		TileInterface(TileType type, int x, int y, bbq::Sprite* sprite, Map* map);
		virtual ~TileInterface();

		virtual TileInterface* getLeft() = 0;
		virtual TileInterface* getRight() = 0;
		virtual TileInterface* getUp() = 0;
		virtual TileInterface* getDown() = 0;

		virtual bool moveLeft() = 0;
		virtual bool moveRight() = 0;
		virtual bool moveUp() = 0;
		virtual bool moveDown() = 0;

		int x_;
		int y_;
		TileType type_;
		bbq::Sprite* sprite_;
		Map* map_;

	};


}
