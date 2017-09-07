#pragma once
#include "../inc/GameObject.h"
#include "../inc/Sprite.h"



class Player : public bbq::GameObject
{
public:
  Player();
  ~Player();

  Player();

  void update() override;
  void draw() override;

  bbq::Sprite sprite;


};

