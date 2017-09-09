#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "../inc/GameObject.h"
#include "../inc/Sprite.h"
#include "../inc./Map.h"
#include "../inc/TileInterface.h"

namespace bbq
{

  class TileMap : public GameObject
  {
  public:
    TileMap() = default;
    TileMap(int width, int height, Map* map);
    ~TileMap();

    void update();
    void draw(SDL_Renderer*, int currentFrame = 0);
    
    Map* map_;
    int columns_;
    int rows_;
  
  };
}

