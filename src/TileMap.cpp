
#include "../inc/globals.h"
#include "../inc/TileMap.h"

namespace bbq
{
  TileMap::TileMap(int width, int height, Map* map) : columns_(width), rows_(height), map_(map)
  {
    //std::copy(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>(), back_inserter(asciiMap_));

    //std::cout << "drawing map" << std::endl;
    //for (auto& c : asciiMap_)
    //{
    //  std::cout << c << std::endl;
    //}


  }

  TileMap::~TileMap()
  {
  }

  void TileMap::update()
  {
  }

  void TileMap::draw(SDL_Renderer * renderer, int currentFrame)
  {
    SDL_Rect destination = { 0, 0, 64 / 2, 64 / 2 };

    for (int col = 0; col < columns_; ++col)
    {
      for (int row = 0; row < rows_; ++row)
      {
        destination.x = col * 64 / 2;
        destination.y = row * 64 / 2;

        TileType tileType = map_->map_[row * columns_ + col];
        Sprite* sprite = type_to_sprite[tileType];
        int index = type_to_sprite_idx[tileType];

        SDL_RenderCopyEx(renderer, sprite->getTexture_(), &sprite->getFrame_(index), &destination, 0, NULL, SDL_FLIP_NONE);


      }
    }
  }
}


