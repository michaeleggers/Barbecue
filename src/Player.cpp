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

void Player::drawAsPixels(SDL_Renderer *renderer, int currentFrame)
{
  SDL_Rect destination = { pos_.x, pos_.y, 64, 64 };
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
  bbq::TileType boxType = playerType_ == bbq::Player1 ? bbq::TileType::Box1 : bbq::TileType::Box2;
  if (tileRight > 1 && tileRight < 16)
  {
    pos_.x++;
    facingState_ = facingState::right;
  }
  else if (tileRight == boxType)
  {
    int box_x = x + 1;
    int box_y = y;
    if (box_x < 0 || box_x >= map_->width)
      return;
    if (box_y < 0 || box_y >= map_->height)
      return;

    int box_idx = box_x + box_y * map_->width;
    bbq::TileType tileBox = map_->map[box_idx];
    if (tileBox > 1 && tileBox < 16)
    {
      int success = SDL_QueueAudio(bbq::deviceId, wavBuffer, wavLength);

      map_->map[box_idx] = boxType;
      map_->map[idx] = bbq::TileType::Free6;
      pos_.x++;
      facingState_ = facingState::right;
    }
  }


}

void Player::moveLeft()
{
  bbq::TileType boxType = playerType_ == bbq::Player1 ? bbq::TileType::Box1 : bbq::TileType::Box2;

  int x = pos_.x - 1;
  int y = pos_.y;
  if (x < 0 || x >= map_->width)
    return;
  if (y < 0 || y >= map_->height)
    return;

  int idx = x + y * map_->width;
  bbq::TileType tileLeft = map_->map[idx];

  if (tileLeft > 1 && tileLeft < 16)
  {
    pos_.x--;
    facingState_ = facingState::left;
  }
  else if (tileLeft == boxType)
  {
    int box_x = x - 1;
    int box_y = y;
    if (box_x < 0 || box_x >= map_->width)
      return;
    if (box_y < 0 || box_y >= map_->height)
      return;

    int box_idx = box_x + box_y * map_->width;
    bbq::TileType tileBox = map_->map[box_idx];
    if (tileBox > 1 && tileBox < 16)
    {
      int success = SDL_QueueAudio(bbq::deviceId, wavBuffer, wavLength);

      map_->map[box_idx] = boxType;
      map_->map[idx] = bbq::TileType::Free6;
      pos_.x--;
      facingState_ = facingState::left;
    }
  }
}

void Player::moveUp()
{
  bbq::TileType boxType = playerType_ == bbq::Player1 ? bbq::TileType::Box1 : bbq::TileType::Box2;

  int x = pos_.x;
  int y = pos_.y - 1;
  if (x < 0 || x >= map_->width)
    return;
  if (y < 0 || y >= map_->height)
    return;

  int idx = x + y * map_->width;
  bbq::TileType tileUp = map_->map[idx];

  if (tileUp > 1 && tileUp < 16)
  {
    pos_.y--;
  }
  else if (tileUp == boxType)
  {
    int box_x = x;
    int box_y = y - 1;
    if (box_x < 0 || box_x >= map_->width)
      return;
    if (box_y < 0 || box_y >= map_->height)
      return;

    int box_idx = box_x + box_y * map_->width;
    bbq::TileType tileBox = map_->map[box_idx];
    if (tileBox > 1 && tileBox < 16)
    {
      int success = SDL_QueueAudio(bbq::deviceId, wavBuffer, wavLength);

      map_->map[box_idx] = boxType;
      map_->map[idx] = bbq::TileType::Free6;
      pos_.y--;
    }
  }
}

void Player::moveDown()
{
  bbq::TileType boxType = playerType_ == bbq::Player1 ? bbq::TileType::Box1 : bbq::TileType::Box2;

  int x = pos_.x;
  int y = pos_.y + 1;
  if (x < 0 || x >= map_->width)
    return;
  if (y < 0 || y >= map_->height)
    return;

  int idx = x + y * map_->width;
  bbq::TileType tileDown = map_->map[idx];

  if (tileDown > 1 && tileDown < 16)
  {
    pos_.y++;
  }
  else if (tileDown == boxType)
  {
    int box_x = x;
    int box_y = y + 1;
    if (box_x < 0 || box_x >= map_->width)
      return;
    if (box_y < 0 || box_y >= map_->height)
      return;

    int box_idx = box_x + box_y * map_->width;
    bbq::TileType tileBox = map_->map[box_idx];
    if (tileBox > 1 && tileBox < 16)
    {
      int success = SDL_QueueAudio(bbq::deviceId, wavBuffer, wavLength);

      map_->map[box_idx] = boxType;
      map_->map[idx] = bbq::TileType::Free6;
      pos_.y++;
    }
  }
}

Player::Player(std::vector<bbq::Sprite *>& sprites, bbq::Map* map, bbq::TileType playerType) :
  map_(map),
  state_(idle),
  sprites_(sprites),
  activeSprite_(sprites_[idle]),
  facingState_(right),
  playerType_(playerType)
{
  SDL_LoadWAV("..\\resources\\box_move.wav", &wavSpec, &wavBuffer, &wavLength);
  bbq::deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

  SDL_PauseAudioDevice(bbq::deviceId, 0);
}




Player::~Player()
{
  SDL_FreeWAV(wavBuffer);
}
