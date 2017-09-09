#pragma once

#include "../inc/Sprite.h"
#include "../inc/Map.h"
namespace bbq
{
  enum TileType : int
  {
    Player1 = 0,
    Player2 = 1,
    Free = 2,
    Free2 = 2,
    Free3 = 2,
    Free4 = 2,
    Free5 = 2,
    Free6 = 2,
    Free7 = 2,
    Free8 = 2,
    Free9 = 2,
    Free10 = 2,
    Free11 = 2,
    Free12 = 2,
    Free13 = 2,
    Free14 = 2,
    Box1 = 3,
    Box2 = 4,
    Wall = 5,
    Wall2 =5
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
