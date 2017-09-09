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
    Free2 = 3,
    Free3 = 4,
    Free4 = 5,
    Free5 = 6,
    Free6 = 7,
    Free7 = 8,
    Free8 = 9,
    Free9 = 10,
    Free10 = 11,
    Free11 = 12,
    Free12 = 13,
    Free13 = 14,
    Free14 = 15,
    Box1 = 16,
    Box2 = 17,
    Wall = 18,
    Wall2 =19
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
