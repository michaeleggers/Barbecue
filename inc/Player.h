#pragma once

#include <vector>

#include "../inc/GameObject.h"
#include "../inc/Sprite.h"
#include "../inc/Map.h"
#include "../inc/TileInterface.h"

enum animationState
{
  idle,
  walk,
  attack
};

enum facingState
{
  right,
  left
};

struct Pos2d_t
{
  int x;
  int y;
};


class Player : public bbq::GameObject
{
public:
  Player();
  Player(std::vector<bbq::Sprite*>& sprites, bbq::Map* map, bbq::TileType playerType);
  ~Player();

  void update() override;
  void draw(SDL_Renderer*, int currentFrame = 0) override;
  void drawAsPixels(SDL_Renderer*, int currentFrame);
  void moveRight();
  void moveLeft();
  void moveUp();
  void moveDown();
  std::vector<bbq::Sprite*> sprites_;
  bbq::Sprite* activeSprite_;
  Pos2d_t pos_;
  animationState state_;
  animationState prevState_;
  facingState facingState_;
  bbq::Map* map_;
  bbq::TileType playerType_;
};

