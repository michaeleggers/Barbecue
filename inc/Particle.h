#pragma once

#include "SDL.h"
#include "../inc/Sprite.h"
namespace bbq
{


  class Particle {

  public:
    Particle(int x, int y,
      int w, int h,
      Uint32 timeToLive, bbq::Sprite* sprite) : destination_{ x, y, w, h }, sprite_(sprite)
    {

      ttl = timeToLive;
      birthDate = SDL_GetTicks();
    }

    void draw(SDL_Renderer *  renderer, int currentFrame) {
      SDL_RenderCopyEx(renderer, sprite_->getTexture_(), &sprite_->getFrame_(currentFrame), &destination_, 0, NULL, SDL_FLIP_HORIZONTAL);

    }

    void move(int x, int y) {
      destination_.x += x;
      destination_.y += y;
    }

    float getTTL() { return ttl; }

    bool isDead() { return SDL_GetTicks() - birthDate > ttl ? true : false; }


    SDL_Rect rect;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint32 ttl;
    Uint32 birthDate;
    bbq::Sprite* sprite_;
    SDL_Rect destination_;

  };

}