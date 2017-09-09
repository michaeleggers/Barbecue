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

int last_update_time = 0;

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
		player2.moveRight();
		//int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	}
	if (iCore.keyHit(SDL_SCANCODE_LEFT))
	{
    player2.moveLeft();
		//int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	}
	if (iCore.keyHit(SDL_SCANCODE_DOWN))
	{
    player2.moveDown();
		//int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	}
	if (iCore.keyHit(SDL_SCANCODE_UP))
	{
    player2.moveUp();
		//int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	}

	if (iCore.keyHit(SDL_SCANCODE_W))
	{
    player1.moveUp();
	}
	if (iCore.keyHit(SDL_SCANCODE_A))
	{
    player1.moveLeft();
	}
	if (iCore.keyHit(SDL_SCANCODE_S))
	{
    player1.moveDown();
	}
	if (iCore.keyHit(SDL_SCANCODE_D))
	{
    player1.moveRight();
	}

	map.draw(gCore.getRenderer());
  static int curFrame = 0;
  static int curFrame2 = 1;
  static int last_update_time_player = 0;
  if (SDL_GetTicks() - last_update_time_player > 150)
  {
    curFrame++;
    if (curFrame >= player1.sprites_[player1.state_]->frameCnt_())
      curFrame = 0;
    curFrame2++;
    if (curFrame2 >= player2.sprites_[player2.state_]->frameCnt_())
      curFrame2 = 0;

    last_update_time_player = SDL_GetTicks();
  }
	player1.draw(gCore.getRenderer(), curFrame);
	player2.draw(gCore.getRenderer(), curFrame2);
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


	bbq::SpriteSheet mapSheet(gCore.getRenderer(), "..\\resources\\map\\tileset.png", 0x00000000);
  bbq::SpriteSheet player1animationSheet(gCore.getRenderer(), "..\\resources\\map\\pigwalk_female-Sheet.png", 0x00000000);
  bbq::SpriteSheet player2animationSheet(gCore.getRenderer(), "..\\resources\\map\\pigwalk_male-Sheet.png", 0x00000000);
  bbq::SpriteSheet heartParticleSheet(gCore.getRenderer(), "..\\resources\\heart_particle.png", 0x00000000);


  bbq::SpriteSheet player1animationSheetIdle(gCore.getRenderer(), "..\\resources\\map\\pigidle_female-Sheet.png", 0x00000000);
  bbq::SpriteSheet player2animationSheetIdle(gCore.getRenderer(), "..\\resources\\map\\pigidle_male-Sheet.png", 0x00000000);


	bbq::Sprite mapSprite(&mapSheet, 64, 64, 0, 0, 25);
	bbq::Sprite playerSprite(&player1animationSheetIdle, 64, 64, 0, 0, 2);
  bbq::Sprite playerSprite2(&player2animationSheetIdle, 64, 64, 0, 0, 2);
  bbq::Sprite player1SpriteAnimation(&player1animationSheet, 64, 64, 0, 0, 3);
  bbq::Sprite player2SpriteAnimation(&player2animationSheet, 64, 64, 0, 0, 3);
  heartAnimationSprite = bbq::Sprite(&heartParticleSheet, 64, 64, 0, 0, 1);

  bbq::type_to_sprite[bbq::TileType::Free] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Free] = 15;
  bbq::type_to_sprite[bbq::TileType::Free2] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Free2] = 13;
  bbq::type_to_sprite[bbq::TileType::Free3] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Free3] = 14;
  bbq::type_to_sprite[bbq::TileType::Free4] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Free4] = 5;
  bbq::type_to_sprite[bbq::TileType::Free5] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Free5] = 8;
  bbq::type_to_sprite[bbq::TileType::Free6] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Free6] = 2;
  bbq::type_to_sprite[bbq::TileType::Free7] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Free7] = 10;
  bbq::type_to_sprite[bbq::TileType::Free8] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Free8] = 9;
  bbq::type_to_sprite[bbq::TileType::Free9] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Free9] = 7;
  bbq::type_to_sprite[bbq::TileType::Free10] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Free10] = 3;
  bbq::type_to_sprite[bbq::TileType::Free11] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Free11] = 4;
  bbq::type_to_sprite[bbq::TileType::Free12] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Free12] = 29;

	bbq::type_to_sprite[bbq::TileType::Box1] = &mapSprite;
	bbq::type_to_sprite_idx[bbq::TileType::Box1] = 6;
  bbq::type_to_sprite[bbq::TileType::Box2] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Box2] = 11;

  bbq::type_to_sprite[bbq::TileType::Wall] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Wall] = 1;
  bbq::type_to_sprite[bbq::TileType::Wall2] = &mapSprite;
  bbq::type_to_sprite_idx[bbq::TileType::Wall2] = 12;

reset:
  fooooo.Load("..\\resources\\map\\Endboss.json");
	map = bbq::TileMap(fooooo.width, fooooo.height, &fooooo);
	/*
	Player1,
	Player2,
	Free,
	Box*/
	std::vector<bbq::Sprite*> playerSprites = { &playerSprite };
	player1 = Player(playerSprites, &fooooo, bbq::TileType::Player1);
	player1.pos_.x = 4;
	player1.pos_.y = 13;

  std::vector<bbq::Sprite*> playerSprites2 = { &playerSprite2 };
	player2 = Player(playerSprites2, &fooooo, bbq::TileType::Player2);
	player2.pos_.x = 35;
	player2.pos_.y = 2;

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
	last_update_time = SDL_GetTicks();
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

    if (state == State::Running)
      doRunning();
    else if (state == State::End)
      doEnd();

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