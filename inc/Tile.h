#pragma once
#include "../inc/TileInterface.h"

namespace bbq
{

  class Tile : public TileInterface
  {
  public:
    Tile(TileType type, int x, int y, bbq::Sprite* sprite);
    ~Tile();

    virtual TileInterface* getLeft();
    virtual TileInterface* getRight();
    virtual TileInterface* getUp();
    virtual TileInterface* getDown();

    virtual bool moveLeft();
    virtual bool moveRight();
    virtual bool moveUp();
    virtual bool moveDown();
  };
}

