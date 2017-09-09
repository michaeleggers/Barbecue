#include <iostream>
#include <string>
#include <map>
#include <list>
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
#include "../inc/Particle.h"

size_t delay = 100;
const int FPS = 60;
const float DELAY_TIME = 1000.0f / FPS;

std::map<bbq::TileType, bbq::Sprite*> bbq::type_to_sprite;
std::map<bbq::TileType, int> bbq::type_to_sprite_idx;

Player player1;
Player player2;

Player player1animation;
Player player2animation;

std::list<bbq::Particle> particles;
bbq::Sprite heartAnimationSprite;

bbq::GraphicsCore gCore;
bbq::InputCore iCore;
bbq::Map fooooo;
bbq::TileMap map;

//SDL_AudioSpec wavSpec;
//Uint32 wavLength;
//Uint8 *wavBuffer;
SDL_AudioDeviceID bbq::deviceId;

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
		//int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	}
	if (iCore.keyHit(SDL_SCANCODE_LEFT))
	{
		player1.moveLeft();
		//int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	}
	if (iCore.keyHit(SDL_SCANCODE_DOWN))
	{
		player1.moveDown();
		//int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	}
	if (iCore.keyHit(SDL_SCANCODE_UP))
	{
		player1.moveUp();
		//int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
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
  int size = rand() % 10;
  bbq::Particle p(640, 680, size, size, 10000, &heartAnimationSprite);

  if (particles.size() < 1000) {
    particles.push_back(p);
  }

  for (auto iter = particles.begin(); iter != particles.end(); ++iter) {
    if (iter->isDead())
      iter = particles.erase(iter);
  }

  for (auto iter = particles.begin(); iter != particles.end(); ++iter) {
    iter->move(cos(rand()) * 4, fabs(sin(rand())) * -5);
    iter->draw(gCore.getRenderer(), 0);
  }
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

	//SDL_LoadWAV("..\\resources\\box_move.wav", &wavSpec, &wavBuffer, &wavLength);
	//bbq::deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

	//SDL_PauseAudioDevice(bbq::deviceId, 0);


	bbq::SpriteSheet mapSheet(gCore.getRenderer(), "..\\resources\\map.png", 0x00000000);
  bbq::SpriteSheet player1animationSheet(gCore.getRenderer(), "..\\resources\\maps\\pig-Sheet.png", 0x00000000);
  bbq::SpriteSheet player2animationSheet(gCore.getRenderer(), "..\\resources\\maps\\pig-Sheet.png", 0x00000000);
  bbq::SpriteSheet heartParticleSheet(gCore.getRenderer(), "..\\resources\\heart_particle.png", 0x00000000);


	bbq::Sprite mapSprite(&mapSheet, 64, 64, 0, 0, 25);
	bbq::Sprite playerSprite(&mapSheet, 64, 64, 0, 0, 2);
  bbq::Sprite player1SpriteAnimation(&player1animationSheet, 64, 64, 0, 0, 3);
  bbq::Sprite player2SpriteAnimation(&player2animationSheet, 64, 64, 0, 0, 3);
  heartAnimationSprite = bbq::Sprite(&heartParticleSheet, 64, 64, 0, 0, 1);


	bbq::type_to_sprite[bbq::TileType::Player1] = &mapSprite;
	bbq::type_to_sprite_idx[bbq::TileType::Player1] = 0;

	bbq::type_to_sprite[bbq::TileType::Player2] = &mapSprite;
	bbq::type_to_sprite_idx[bbq::TileType::Player2] = 1;

	bbq::type_to_sprite[bbq::TileType::Free] = &mapSprite;
	bbq::type_to_sprite_idx[bbq::TileType::Free] = 2;

	bbq::type_to_sprite[bbq::TileType::Box1] = &mapSprite;
	bbq::type_to_sprite_idx[bbq::TileType::Box1] = 3;

	bbq::type_to_sprite[bbq::TileType::Wall] = &mapSprite;
	bbq::type_to_sprite_idx[bbq::TileType::Wall] = 4;

  bbq::type_to_sprite[bbq::TileType::Box2] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Box2] = 1;

reset:
  fooooo.Load("..\\resources\\map\\test.json");
	map = bbq::TileMap(fooooo.width, fooooo.height, &fooooo);
	/*
	Player1,
	Player2,
	Free,
	Box*/
	std::vector<bbq::Sprite*> playerSprites = { &playerSprite };
	player1 = Player(playerSprites, &fooooo, bbq::TileType::Player1);
	player1.pos_.x = 4;
	player1.pos_.y = 3;

	player2 = Player(playerSprites, &fooooo, bbq::TileType::Player2);
	player2.pos_.x = 4;
	player2.pos_.y = 5;

  std::vector<bbq::Sprite*> player1Sprites = { &player1SpriteAnimation };
  player1animation = Player(player1Sprites, &fooooo, bbq::TileType::Player1);
  player1animation.pos_.x = 0;
  player1animation.pos_.y = 650;

  std::vector<bbq::Sprite*> player2Sprites = { &player2SpriteAnimation };
  player2animation = Player(player2Sprites, &fooooo, bbq::TileType::Player2);
  player2animation.pos_.x = 1280 - 64;
  player2animation.pos_.y = 650;
  player2animation.facingState_ = facingState::left;


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
      if (iCore.keyDown(SDL_SCANCODE_R))
      {
        goto reset;
      }

			if (iCore.keyDown(SDL_SCANCODE_ESCAPE))
			{
				running = false;
			}

			last_update_time_input = SDL_GetTicks();
		}

		// player animation:
		if (SDL_GetTicks() - last_update_time > 75)
		{
			currentFrame++;
			if (currentFrame >= player1animation.sprites_[player1animation.state_]->frameCnt_())
				currentFrame = 0;
      currentFrame2++;
      if (currentFrame2 >= player2animation.sprites_[player2animation.state_]->frameCnt_())
        currentFrame2 = 0;

			last_update_time = SDL_GetTicks();
		}

		if (state == State::Running)
			doRunning();
		else if (state == State::End)
			doEnd();



		if (player1.pos_.x == player2.pos_.x && player1.pos_.y == player2.pos_.y)
		{
			state = State::End;
		}

    int deltaX = abs(player1.pos_.x - player2.pos_.x) * 32;
    int deltaY = abs(player1.pos_.y - player2.pos_.y) * 32;

    int distance = sqrt(deltaX *deltaX + deltaY*deltaY);
    int distanceHalfed = distance / 2;

    player1animation.pos_.x = 576 - distanceHalfed;
    player2animation.pos_.x = 640 + distanceHalfed;

    player1animation.drawAsPixels(gCore.getRenderer(), currentFrame);
    player2animation.drawAsPixels(gCore.getRenderer(), currentFrame2);

		SDL_RenderPresent(gCore.getRenderer());
		//SDL_Delay(100); // artificial render time 

		after_render_time = SDL_GetTicks();
		time_needed = after_render_time - before_render_time;

		if (time_needed < DELAY_TIME)
		{
			SDL_Delay(DELAY_TIME - time_needed);
		}

	}

	SDL_CloseAudioDevice(bbq::deviceId);

	SDL_Quit();

	return 0;
}