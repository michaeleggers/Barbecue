#include "../inc/Player.h"

Player::Player()
{
}

void Player::update()
{
  if (state_ == idle)
  {
    activeSprite_ = sprites_[0];
  }
  else if (state_ == walk)
  {
    activeSprite_ = sprites_[1];
  }
  else if (state_ == attack)
  {
    if (prevState_ != attack)
    {
      activeSprite_ = sprites_[2];
    }
  }
  else
  {
    state_ = idle;
  }

  prevState_ = state_;

}

void Player::draw(SDL_Renderer * renderer, int currentFrame)
{
  SDL_Rect destination = { pos_.x * 32, pos_.y * 32, 32, 32 };
  if (facingState_ == facingState::left)
  {
    SDL_RenderCopyEx(renderer, activeSprite_->getTexture_(), &activeSprite_->getFrame_(currentFrame), &destination, 0, NULL, SDL_FLIP_HORIZONTAL);
  }
  else
  {
    SDL_RenderCopyEx(renderer, activeSprite_->getTexture_(), &activeSprite_->getFrame_(currentFrame), &destination, 0, NULL, SDL_FLIP_NONE);
  }
}

void Player::moveRight()
{
  int x = pos_.x + 1;
  int y = pos_.y;
  if (x < 0 || x >= map_->width)
    return;
  if (y < 0 || y >= map_->height)
    return;

  int idx = x + y * map_->width;
  bbq::TileType tileRight = map_->map[idx];

  if (tileRight == bbq::TileType::Free)
  {
    pos_.x++;
  }
  else if (tileRight == bbq::TileType::Box)
  {
    int box_x = x + 1;
    int box_y = y;
    if (box_x < 0 || box_x >= map_->width)
      return;
    if (box_y < 0 || box_y >= map_->height)
      return;

    int box_idx = box_x + box_y * map_->width;
    bbq::TileType tileBox = map_->map[box_idx];
    if (tileBox == bbq::TileType::Free)
    {
      map_->map[box_idx] = bbq::TileType::Box;
      map_->map[idx] = bbq::TileType::Free;
      pos_.x++;
    }
  }


}

void Player::moveLeft()
{
  int x = pos_.x - 1;
  int y = pos_.y;
  if (x < 0 || x >= map_->width)
    return;
  if (y < 0 || y >= map_->height)
    return;

  int idx = x + y * map_->width;
  bbq::TileType tileLeft = map_->map[idx];

  if (tileLeft == bbq::TileType::Free)
  {
    pos_.x--;
  }
  else if (tileLeft == bbq::TileType::Box)
  {
    int box_x = x - 1;
    int box_y = y;
    if (box_x < 0 || box_x >= map_->width)
      return;
    if (box_y < 0 || box_y >= map_->height)
      return;

    int box_idx = box_x + box_y * map_->width;
    bbq::TileType tileBox = map_->map[box_idx];
    if (tileBox == bbq::TileType::Free)
    {
      map_->map[box_idx] = bbq::TileType::Box;
      map_->map[idx] = bbq::TileType::Free;
      pos_.x--;
    }
  }
}

void Player::moveUp()
{
  int x = pos_.x;
  int y = pos_.y - 1;
  if (x < 0 || x >= map_->width)
    return;
  if (y < 0 || y >= map_->height)
    return;

  int idx = x + y * map_->width;
  bbq::TileType tileUp = map_->map[idx];

  if (tileUp == bbq::TileType::Free)
  {
    pos_.y--;
  }
  else if (tileUp == bbq::TileType::Box)
  {
    int box_x = x;
    int box_y = y - 1;
    if (box_x < 0 || box_x >= map_->width)
      return;
    if (box_y < 0 || box_y >= map_->height)
      return;

    int box_idx = box_x + box_y * map_->width;
    bbq::TileType tileBox = map_->map[box_idx];
    if (tileBox == bbq::TileType::Free)
    {
      map_->map[box_idx] = bbq::TileType::Box;
      map_->map[idx] = bbq::TileType::Free;
      pos_.y--;
    }
  }
}

void Player::moveDown()
{
  int x = pos_.x;
  int y = pos_.y + 1;
  if (x < 0 || x >= map_->width)
    return;
  if (y < 0 || y >= map_->height)
    return;

  int idx = x + y * map_->width;
  bbq::TileType tileDown = map_->map[idx];

  if (tileDown == bbq::TileType::Free)
  {
    pos_.y++;
  }
  else if (tileDown == bbq::TileType::Box)
  {
    int box_x = x;
    int box_y = y + 1;
    if (box_x < 0 || box_x >= map_->width)
      return;
    if (box_y < 0 || box_y >= map_->height)
      return;

    int box_idx = box_x + box_y * map_->width;
    bbq::TileType tileBox = map_->map[box_idx];
    if (tileBox == bbq::TileType::Free)
    {
      map_->map[box_idx] = bbq::TileType::Box;
      map_->map[idx] = bbq::TileType::Free;
      pos_.y++;
    }
  }
}

Player::Player(std::vector<bbq::Sprite *>& sprites, bbq::Map* map) :
  map_(map),
  state_(idle),
  sprites_(sprites),
  activeSprite_(sprites_[idle]),
  facingState_(right),
  pos_{ 0, 0 }
{
}




Player::~Player()
{
}
