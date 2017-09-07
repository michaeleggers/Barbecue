#pragma once


namespace bbq
{

  class GameObject
  {
  public:
    GameObject();
    virtual ~GameObject();

    virtual void update() = 0;
    virtual void draw() = 0;

  };
}

