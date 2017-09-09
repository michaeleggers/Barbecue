#include "../inc/TileInterface.h"

namespace bbq
{

  TileInterface::TileInterface(TileType type, int x, int y, bbq::Sprite* sprite, Map* map) : type_(type), x_(x), y_(y), sprite_(sprite), map_(map)
  {
  }


  TileInterface::~TileInterface()
  {
  }
}

