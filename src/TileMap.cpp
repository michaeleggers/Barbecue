

#include "../inc/TileMap.h"

namespace bbq
{
  TileMap::TileMap(std::string const & inputfile, int width, int height, Sprite* sprite, Map* map) : columns_(width), rows_(height), sprite_(sprite), map_(map)
  {
    std::ifstream ifs(inputfile);
    //std::copy(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>(), back_inserter(asciiMap_));

    //std::cout << "drawing map" << std::endl;
    //for (auto& c : asciiMap_)
    //{
    //  std::cout << c << std::endl;
    //}

    asciiMap_ = { '#', '#', '#','#', '#', '#','#', '#', '#','#', '#', '#',
            '#', '#', '#','#', '#', '#','#', '#', '#','#', '#', '#',
            '#', '#', '#','#', '#', '#','#', '#', '#','#', '#', '#',
            '#', '#', '#','0', '0', '0','0', '#', '#','#', '#', '#',
            '#', '#', '#','0', '0', '0','0', '#', '#','#', '#', '#',
            '#', '#', '#','0', '0', '0','0', '#', '#','#', '#', '#',
            '#', '#', '#','#', '#', '#','#', '#', '#','#', '#', '#',
            '#', '#', '#','#', '#', '#','#', '#', '#','#', '#', '#'
    };
    std::cout << "map size: " << asciiMap_.size() << std::endl;
    ifs.close();
  }

  TileMap::~TileMap()
  {
  }

  void TileMap::update()
  {
  }

  void TileMap::draw(SDL_Renderer * renderer, int currentFrame)
  {
    SDL_Rect destination = { 0, 0, sprite_->width_ , sprite_->height_ };

    for (int col = 0; col < columns_; ++col)
    {
      for (int row = 0; row < rows_; ++row)
      {
        destination.x = col * sprite_->width_;
        destination.y = row * sprite_->height_;

        char tile = asciiMap_[row * columns_ + col];
        TileType tileType = map_[row * columns_ + col];
        if (tileType == TileType::Free)
        {
          SDL_RenderCopyEx(renderer, sprite_->getTexture_(), &sprite_->getFrame_(0), &destination, 0, NULL, SDL_FLIP_NONE);
        }
        if (tileType == TileType::Box)
        {
          SDL_RenderCopyEx(renderer, sprite_->getTexture_(), &sprite_->getFrame_(1), &destination, 0, NULL, SDL_FLIP_NONE);
        }
      }
    }
  }
}


