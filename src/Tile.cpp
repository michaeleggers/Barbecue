#include "..\inc\Tile.h"

using namespace bbq;

Tile::Tile(TileType type, int x, int y, bbq::Sprite * sprite) : TileInterface(type, x, y, sprite)
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
  nullptr;
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
