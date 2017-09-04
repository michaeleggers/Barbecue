#pragma once

#include <iostream>

#include "SDL.h"

class GraphicsCore
{
public:
  GraphicsCore();
  ~GraphicsCore();

  int init();
  int clear();
  SDL_Renderer* getRenderer();

private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;

  
};

