#include "../inc/GraphicsCore.h"


GraphicsCore::GraphicsCore()
{
}

GraphicsCore::~GraphicsCore()
{
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
}

int GraphicsCore::init()
{
  int errorCode = 0;
  if (errorCode = (SDL_Init(SDL_INIT_EVERYTHING) < 0)) 
  {
    std::cout << "couldn't init SDL2. ERROR: " << SDL_GetError() << std::endl;
  }
  
  window_ = SDL_CreateWindow(
    "Barbecue",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    800, 600,
    0
  );

  renderer_ = SDL_CreateRenderer(window_, -1, 0);
  SDL_RenderSetLogicalSize(renderer_, 320, 240);

  return errorCode;
}

int GraphicsCore::clear()
{
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);
  return 0;
}

SDL_Renderer * GraphicsCore::getRenderer()
{
  return renderer_;
}
