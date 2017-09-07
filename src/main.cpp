#include <iostream>
#include "SDL.h"
/* Graphics */
#include "../inc/Sprite.h"
#include "../inc/SpriteSheet.h"
#include "../inc/GraphicsCore.h"
/* Input */
#include "../inc/InputCore.h"



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
	bbq::Sprite sprite(&spriteSheet, 36, 36, 0, 36, 6);
	bbq::Sprite sprite2(&spriteSheet, 36, 36, 0, 72, 4);
  sprite.setScale(2, 2);
	SDL_Rect dest2 = { 72, 72, 72, 72 };
  // init pos of player
  float destX = 0.0f;
  float destY = 0.0f;

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
    if (SDL_GetTicks() - last_update_time_input > 10) 
    {
      iCore.update();
      if (iCore.keyDown(SDL_SCANCODE_RIGHT))
      {
        std::cout << std::to_string(5.f * time_needed) << std::endl;
        destX += 5;
      }
      if (iCore.keyDown(SDL_SCANCODE_LEFT))
      {
        //std::cout << "left arrow key pressed" << std::endl;
        destX -= 5;
      }
      if (iCore.keyDown(SDL_SCANCODE_DOWN))
      {
        //std::cout << "left arrow key pressed" << std::endl;
        destY += 5;
      }
      if (iCore.keyDown(SDL_SCANCODE_UP))
      {
        //std::cout << "left arrow key pressed" << std::endl;
        destY -= 5;
      }
      if (iCore.keyDown(SDL_SCANCODE_ESCAPE))
      {
        //std::cout << "left arrow key pressed" << std::endl;
        running = false;
      }
      last_update_time_input = SDL_GetTicks();
    }
      sprite.setPos((int)destX, (int)destY);

		// for controlling update speed of animation
		if (SDL_GetTicks() - last_update_time > 100) {
			currentFrame++;
			currentFrame2++;
			if (currentFrame >= sprite.frameCnt_())
				currentFrame = 0;

			if (currentFrame2 >= sprite2.frameCnt_())
				currentFrame2 = 0;
			last_update_time = SDL_GetTicks();
		}

		//SDL_SetRenderDrawColor(rdr_main, 0.2, 0.2, 0.2, 255);
    gCore.clear();
		//SDL_RenderClear(rdr_main);
		//SDL_RenderCopy(rdr_main, texture, NULL, NULL);

		// SDL_RenderCopyEx same as SDL_RenderCopy but provides more features such as flipping and rotating.
    SDL_RenderCopyEx(gCore.getRenderer(), sprite.getTexture_(), &sprite.getFrame_(currentFrame), &sprite.getPosAndScale(), 0, NULL, SDL_FLIP_HORIZONTAL);
		SDL_RenderCopyEx(gCore.getRenderer(), sprite2.getTexture_(), &sprite2.getFrame_(currentFrame2), &dest2, 0, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(gCore.getRenderer());
		//SDL_Delay(50); // artificial render time 

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