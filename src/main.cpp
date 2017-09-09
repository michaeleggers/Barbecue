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

using namespace std;

size_t delay = 100;
const int FPS = 60;
const float DELAY_TIME = 1000.0f / FPS;

std::map<bbq::TileType, bbq::Sprite*> bbq::type_to_sprite;
std::map<bbq::TileType, int> bbq::type_to_sprite_idx;

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

	bbq::Map fooooo;
	fooooo.Load("..\\resources\\map\\test.json");

	bbq::SpriteSheet sheet(gCore.getRenderer(), "..\\resources\\map.png", 0x00000000);
	bbq::Sprite sprite(&sheet, 64, 64, 0, 0, 25);

	bbq::type_to_sprite[bbq::TileType::Player1] = &sprite;
	bbq::type_to_sprite_idx[bbq::TileType::Player1] = 0;

  bbq::type_to_sprite[bbq::TileType::Player2] = &sprite;
  bbq::type_to_sprite_idx[bbq::TileType::Player2] = 1;
	
  bbq::type_to_sprite[bbq::TileType::Free] = &sprite;
  bbq::type_to_sprite_idx[bbq::TileType::Free] = 2;

  bbq::type_to_sprite[bbq::TileType::Box] = &sprite;
  bbq::type_to_sprite_idx[bbq::TileType::Box] = 3;

  bbq::type_to_sprite[bbq::TileType::Wall] = &sprite;
  bbq::type_to_sprite_idx[bbq::TileType::Wall] = 4;

  bbq::TileMap map(fooooo.width, fooooo.height, &fooooo);
		/*
		Player1,
		Player2,
		Free,
		Box*/
	
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
		//if (SDL_GetTicks() - last_update_time_input > 0) // not quite what the threshold should be
		//{
		//	iCore.update();
		//	if (iCore.keyDown(SDL_SCANCODE_RIGHT))
		//	{
		//		player.state_ = walk;
		//		player.facingState_ = facingState::right;
		//		player.pos_.x += 8;
		//	}
		//	if (iCore.keyDown(SDL_SCANCODE_LEFT))
		//	{
		//		player.state_ = walk;
		//		player.facingState_ = facingState::left;
		//		player.pos_.x -= 8;
		//	}
		//	if (iCore.keyDown(SDL_SCANCODE_DOWN))
		//	{
		//		player.pos_.y += 1;
		//	}
		//	if (iCore.keyDown(SDL_SCANCODE_UP))
		//	{
		//		player.pos_.y -= 1;
		//	}
		//	if (iCore.keyUp(SDL_SCANCODE_RIGHT))
		//	{
		//		player.state_ = idle;
		//	}
		//	if (iCore.keyUp(SDL_SCANCODE_LEFT))
		//	{
		//		player.state_ = idle;
		//	}
		//	if (iCore.keyDown(SDL_SCANCODE_SPACE))
		//	{
		//		player.state_ = attack;
		//	}

		//	if (iCore.keyDown(SDL_SCANCODE_ESCAPE))
		//	{
		//		running = false;
		//	}

		//	if (iCore.keyDown(SDL_SCANCODE_D))
		//	{
		//		player2.state_ = walk;
		//		player2.facingState_ = facingState::right;
		//		player2.pos_.x += 2;
		//	}
		//	if (iCore.keyDown(SDL_SCANCODE_A))
		//	{
		//		player2.state_ = walk;
		//		player2.facingState_ = facingState::left;
		//		player2.pos_.x -= 2;
		//	}
		//	if (iCore.keyUp(SDL_SCANCODE_D))
		//	{
		//		player2.state_ = idle;
		//	}
		//	if (iCore.keyUp(SDL_SCANCODE_A))
		//	{
		//		player2.state_ = idle;
		//	}

		//	player.update();
		//	player2.update();

		//	last_update_time_input = SDL_GetTicks();
		//}

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

		//SDL_SetRenderDrawColor(rdr_main, 0.2, 0.2, 0.2, 255);
		gCore.clear();
		//SDL_RenderClear(rdr_main);
		//SDL_RenderCopy(rdr_main, texture, NULL, NULL);

		//SDL_RenderCopyEx same as SDL_RenderCopy but provides more features such as flipping and rotating.

		
		//player.draw(gCore.getRenderer(), currentFrame);
		//player2.draw(gCore.getRenderer(), currentFrame2);
    map.draw(gCore.getRenderer());
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