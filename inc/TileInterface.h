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
    Box
  };

  class TileInterface
  {
  public:
    TileInterface(TileType type, int x, int y, bbq::Sprite* sprite, Map* map);
    virtual ~TileInterface();

    virtual TileInterface* getLeft();
    virtual TileInterface* getRight();
    virtual TileInterface* getUp();
    virtual TileInterface* getDown();

    virtual bool moveLeft();
    virtual bool moveRight();
    virtual bool moveUp();
    virtual bool moveDown();

    int x_;
    int y_;
    TileType type_;
    bbq::Sprite* sprite_;
    Map* map_;
  
  };


}
