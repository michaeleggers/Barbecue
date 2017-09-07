#include <iostream>
#include "SDL.h"
/* Graphics */
#include "../inc/Sprite.h"
#include "../inc/SpriteSheet.h"
#include "../inc/GraphicsCore.h"
/* Input */
#include "../inc/InputCore.h"
/* Custom */
#include "../inc/Player.h"


using namespace std;

size_t delay = 100;
const int FPS = 60;
const float DELAY_TIME = 1000.0f / FPS;


int main(int argc, char** argv)
{



	// Init SDL2 //////////////////////////////////////

  // for now done in graphics core

	// ! Init SDL2 //////////////////////////////////////


  // Init Graphics Core ///////////////////////////////

  bbq::GraphicsCore gCore;
  gCore.init();

  // ! Init Graphics Core /////////////////////////////

  // Init Input Core //////////////////////////////////

  bbq::InputCore iCore;
  iCore.init();

  // ! Init Input Core ////////////////////////////////


	// Test SriteSheet, Sprite classes
	bbq::SpriteSheet spriteSheet(gCore.getRenderer(), "C:\\Users\\Michael Eggers\\Documents\\Barbecue\\resources\\militaWarrior_36x36.png", 0x00000000);
  bbq::SpriteSheet forestSheet(gCore.getRenderer(), "C:\\Users\\Michael Eggers\\Documents\\Barbecue\\resources\\bg.png", 0x00000000);

  bbq::Sprite idleSprite(&spriteSheet, 36, 36, 0, 0, 4);
	bbq::Sprite walkSprite(&spriteSheet, 36, 36, 0, 36, 6);
	bbq::Sprite attackSprite(&spriteSheet, 36, 36, 0, 72, 4);

  bbq::Sprite forestSprite(&forestSheet, 982, 793, 0, 0, 1);
  SDL_Rect forestDest = { 0, 0, 982, 793 };

  // GameObject using the sprites
  std::vector<bbq::Sprite*> playerSprites = {
    &idleSprite,
    &walkSprite,
    &attackSprite
  };
  Player player(playerSprites);
  Player player2(playerSprites);

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
	while (running) {

		before_render_time = SDL_GetTicks();

		while (SDL_PollEvent(&event) != 0) 
    {

			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

    // testing input core -> input process
    // input update
    if (SDL_GetTicks() - last_update_time_input > 8) 
    {
      iCore.update();
      if (iCore.keyDown(SDL_SCANCODE_RIGHT))
      {
        //std::cout << "right arrow key pressed" << std::endl;
        player.state_ = walk;
        player.facingState_ = facingState::right;
        player.pos_.x += 2;
      }
      if (iCore.keyDown(SDL_SCANCODE_LEFT))
      {
        //std::cout << "left arrow key pressed" << std::endl;
        player.state_ = walk;
        player.facingState_ = facingState::left;
        player.pos_.x -= 2;
      }
      if (iCore.keyDown(SDL_SCANCODE_DOWN))
      {
        //std::cout << "down arrow key pressed" << std::endl;
        //player.state_ = idle;
        player.pos_.y += 1;
      }
      if (iCore.keyDown(SDL_SCANCODE_UP))
      {
        //std::cout << "up arrow key pressed" << std::endl;
        //player.state_ = idle;
        player.pos_.y -= 1;
      }
      if (iCore.keyUp(SDL_SCANCODE_RIGHT))
      {
        player.state_ = idle;
      }
      if (iCore.keyUp(SDL_SCANCODE_LEFT))
      {
        player.state_ = idle;
      }
      if (iCore.keyDown(SDL_SCANCODE_SPACE))
      {
        player.state_ = attack;
      }

      if (iCore.keyDown(SDL_SCANCODE_ESCAPE))
      {
        running = false;
      }

      if (iCore.keyDown(SDL_SCANCODE_D))
      {
        //std::cout << "right arrow key pressed" << std::endl;
        player2.state_ = walk;
        player2.facingState_ = facingState::right;
        player2.pos_.x += 2;
      }
      if (iCore.keyDown(SDL_SCANCODE_A))
      {
        //std::cout << "left arrow key pressed" << std::endl;
        player2.state_ = walk;
        player2.facingState_ = facingState::left;
        player2.pos_.x -= 2;
      }
      if (iCore.keyUp(SDL_SCANCODE_D))
      {
        player2.state_ = idle;
      }
      if (iCore.keyUp(SDL_SCANCODE_A))
      {
        player2.state_ = idle;
      }

      player.update();
      player2.update();

      last_update_time_input = SDL_GetTicks();
    }

		if (SDL_GetTicks() - last_update_time > 75)
    {
			currentFrame++;
      currentFrame2++;
			if (currentFrame >= player.sprites_[player.state_]->frameCnt_())
				currentFrame = 0;
      if (currentFrame2 >= player2.sprites_[player2.state_]->frameCnt_())
        currentFrame2 = 0;
      last_update_time = SDL_GetTicks();
		}

		//SDL_SetRenderDrawColor(rdr_main, 0.2, 0.2, 0.2, 255);
    gCore.clear();
		//SDL_RenderClear(rdr_main);
		//SDL_RenderCopy(rdr_main, texture, NULL, NULL);

		// SDL_RenderCopyEx same as SDL_RenderCopy but provides more features such as flipping and rotating.
		SDL_RenderCopyEx(gCore.getRenderer(), forestSprite.getTexture_(), &forestSprite.getFrame_(0), &forestDest, 0, NULL, SDL_FLIP_NONE);
    player.draw(gCore.getRenderer(), currentFrame);
    player2.draw(gCore.getRenderer(), currentFrame2);
		SDL_RenderPresent(gCore.getRenderer());
		//SDL_Delay(100); // artificial render time 

		after_render_time = SDL_GetTicks();
		time_needed = after_render_time - before_render_time;

		if (time_needed < DELAY_TIME) 
    {
			SDL_Delay(DELAY_TIME - time_needed);
		}
		//cout << "time_needed: " << time_needed << endl;
		//cout << "FPS: " << 1000.0f / time_needed << endl;

		// check current frame
    
	}


	SDL_Quit();

	return 0;
}