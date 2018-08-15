#pragma once

#include <iostream>

#include "SDL.h"

namespace bbq
{
  class GraphicsCore
  {
  public:
    GraphicsCore();
    ~GraphicsCore();

    int init();
    int clear();
    SDL_Renderer* getRenderer();
    SDL_Window* window_;
    SDL_Renderer* renderer_;
  };
}

