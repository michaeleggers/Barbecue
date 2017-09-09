#include <iostream>
#include <string>
#include <map>
#include "SDL.h"
/* Graphics */
#include "../inc/Sprite.h"
#include "../inc/SpriteSheet.h"
#include "../inc/GraphicsCore.h"
/* Input */
#include "../inc/InputCore.h"
/* Bitmap font */
#include "../inc/BitmapFont.h"
/* Ascii TileMap */
#include "../inc/TileMap.h"
/* Custom */
#include "../inc/Player.h"
#include "../inc/Map.h"
#include "../inc/globals.h"
#include "../inc/TileInterface.h"

size_t delay = 100;
const int FPS = 60;
const float DELAY_TIME = 1000.0f / FPS;

std::map<bbq::TileType, bbq::Sprite*> bbq::type_to_sprite;
std::map<bbq::TileType, int> bbq::type_to_sprite_idx;

Player player1;
Player player2;

bbq::GraphicsCore gCore;
bbq::InputCore iCore;
bbq::Map fooooo;
bbq::TileMap map;

enum State
{
  Start,
  Running,
  End
};

void doRunning()
{
  if (iCore.keyHit(SDL_SCANCODE_RIGHT))
  {
    player1.moveRight();
  }
  if (iCore.keyHit(SDL_SCANCODE_LEFT))
  {
    player1.moveLeft();
  }
  if (iCore.keyHit(SDL_SCANCODE_DOWN))
  {
    player1.moveDown();
  }
  if (iCore.keyHit(SDL_SCANCODE_UP))
  {
    player1.moveUp();
  }

  if (iCore.keyHit(SDL_SCANCODE_W))
  {
    player2.moveUp();
  }
  if (iCore.keyHit(SDL_SCANCODE_A))
  {
    player2.moveLeft();
  }
  if (iCore.keyHit(SDL_SCANCODE_S))
  {
    player2.moveDown();
  }
  if (iCore.keyHit(SDL_SCANCODE_D))
  {
    player2.moveRight();
  }

  map.draw(gCore.getRenderer());
  player1.draw(gCore.getRenderer());
  player2.draw(gCore.getRenderer());
}

void doEnd()
{

}

int main(int argc, char** argv)
{
  // Init SDL2 //////////////////////////////////////

  // for now done in graphics core

  // ! Init SDL2 //////////////////////////////////////


  // Init Graphics Core ///////////////////////////////

  
  gCore.init();

  // ! Init Graphics Core /////////////////////////////

  // Init Input Core //////////////////////////////////

  
  iCore.init();

  // ! Init Input Core ////////////////////////////////

  
  fooooo.Load("..\\resources\\map\\test.json");

  bbq::SpriteSheet mapSheet(gCore.getRenderer(), "..\\resources\\map.png", 0x00000000);

  bbq::Sprite mapSprite(&mapSheet, 64, 64, 0, 0, 25);
  bbq::Sprite playerSprite(&mapSheet, 64, 64, 0, 0, 2);


  bbq::type_to_sprite[bbq::TileType::Player1] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Player1] = 0;

  bbq::type_to_sprite[bbq::TileType::Player2] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Player2] = 1;

  bbq::type_to_sprite[bbq::TileType::Free] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Free] = 2;

  bbq::type_to_sprite[bbq::TileType::Box] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Box] = 3;

  bbq::type_to_sprite[bbq::TileType::Wall] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Wall] = 4;

  map = bbq::TileMap(fooooo.width, fooooo.height, &fooooo);
  /*
  Player1,
  Player2,
  Free,
  Box*/
  std::vector<bbq::Sprite*> playerSprites = { &playerSprite };
  player1 = Player(playerSprites, &fooooo);
  player1.pos_.x = 4;
  player1.pos_.y = 3;

  player2 = Player(playerSprites, &fooooo);
  player2.pos_.x = 4;
  player2.pos_.y = 5;

  // ! Test SpriteSheet, Sprite classes
  bool running = true;
  size_t iter = 0;
  SDL_Event event;

  int before_update_time = 0;
  int last_update_time = SDL_GetTicks();
  float last_update_time_input = SDL_GetTicks();
  int before_render_time = SDL_GetTicks();
  int after_render_time = 0.0f;
  int time_needed = 0;
  Uint8 currentFrame = 0;
  Uint8 currentFrame2 = 0;
  State state = State::Running;

  while (running) {

    before_render_time = SDL_GetTicks();

    while (SDL_PollEvent(&event) != 0)
    {

      if (event.type == SDL_QUIT) {
        running = false;
      }
    }

    // input
    gCore.clear();
    if (SDL_GetTicks() - last_update_time_input > 0) // not quite what the threshold should be
    {
      iCore.update();


      if (iCore.keyDown(SDL_SCANCODE_ESCAPE))
      {
        running = false;
      }

      last_update_time_input = SDL_GetTicks();
    }

    // player animation:
    //if (SDL_GetTicks() - last_update_time > 75)
    //{
    //	currentFrame++;
    //	currentFrame2++;
    //	if (currentFrame >= player.sprites_[player.state_]->frameCnt_())
    //		currentFrame = 0;
    //	if (currentFrame2 >= player2.sprites_[player2.state_]->frameCnt_())
    //		currentFrame2 = 0;
    //	last_update_time = SDL_GetTicks();
    //}

    if (state == State::Running)
      doRunning();
    else if (state == State::End)
      doEnd();

    

    if (player1.pos_.x == player2.pos_.x && player1.pos_.y == player2.pos_.y)
    {
      state = State::End;
    }

    SDL_RenderPresent(gCore.getRenderer());
    //SDL_Delay(100); // artificial render time 

    after_render_time = SDL_GetTicks();
    time_needed = after_render_time - before_render_time;

    if (time_needed < DELAY_TIME)
    {
      SDL_Delay(DELAY_TIME - time_needed);
    }

  }


  SDL_Quit();

  return 0;
}