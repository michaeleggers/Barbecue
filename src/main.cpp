#include <iostream>
#include "SDL.h"
/* Graphics */
#include "../inc/Sprite.h"
#include "../inc/SpriteSheet.h"




using namespace std;

size_t delay = 100;
const int FPS = 60;
const float DELAY_TIME = 1000.0f / FPS;
const Uint8* keycode;

void process_keypress() {
	//if (keycode[SDL_SCANCODE_LEFT]) {
	//	//delay += 10;
	//	cout << "left key was pressed" << endl;
	//}
	if (keycode[SDL_SCANCODE_LEFT] && keycode[SDL_SCANCODE_RIGHT]) {
		cout << "left and right keys pressed" << endl;
	}
}


int main(int argc, char** argv)
{



	// Init SDL2 //////////////////////////////////////

	SDL_Window* window = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "couldn't init SDL2. ERROR: " << SDL_GetError() << endl;

	}

	window = SDL_CreateWindow("Sprite Test",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800, 600, // 0, 0
		0); // SDL_FULLSCREEN_DESKTOP

	SDL_Renderer *rdr_main = SDL_CreateRenderer(window, -1, 0);
	SDL_RenderSetLogicalSize(rdr_main, 320, 240);

	// ! Init SDL2 //////////////////////////////////////

	// Test SriteSheet, Sprite classes
	
	bbq::SpriteSheet spriteSheet(rdr_main, "C:\\Users\\Michael Eggers\\Documents\\Barbecue\\resources\\militaWarrior_36x36.png", 0x00000000);
	bbq::Sprite sprite(&spriteSheet, 36, 36, 0, 36, 6);
	bbq::Sprite sprite2(&spriteSheet, 36, 36, 0, 72, 4);
	SDL_Rect dest = { 0, 0, 72, 72 }; // for now hardcoded where sprite should appear on screen
	SDL_Rect dest2 = { 72, 72, 72, 72 };

	// ! Test SpriteSheet, Sprite classes
	bool running = true;
	size_t iter = 0;
	SDL_Event event;

	float before_update_time = 0;
	float last_update_time = SDL_GetTicks();
	float before_render_time = SDL_GetTicks();
	float after_render_time = 0.0f;
	float time_needed = 0;
	Uint8 currentFrame = 0;
	Uint8 currentFrame2 = 0;
	while (running) {

		before_render_time = SDL_GetTicks();


		if (delay <= 0) delay = 10;
		keycode = SDL_GetKeyboardState(NULL);
		process_keypress();

		while (SDL_PollEvent(&event) != 0) {

			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

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
		SDL_RenderClear(rdr_main);
		//SDL_RenderCopy(rdr_main, texture, NULL, NULL);

		// SDL_RenderCopyEx same as SDL_RenderCopy but provides more features such as flipping and rotating.
		SDL_RenderCopyEx(rdr_main, sprite.getTexture_(), &sprite.getFrame_(currentFrame), &dest, 0, NULL, SDL_FLIP_HORIZONTAL);
		SDL_RenderCopyEx(rdr_main, sprite2.getTexture_(), &sprite2.getFrame_(currentFrame2), &dest2, 0, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(rdr_main);
		//SDL_Delay(50); // artificial render time 

		after_render_time = SDL_GetTicks();
		time_needed = after_render_time - before_render_time;

		if (time_needed < DELAY_TIME) {
			SDL_Delay(DELAY_TIME - time_needed);
		}
		//cout << "time_needed: " << time_needed << endl;
		//cout << "FPS: " << 1000.0f / time_needed << endl;

		// check current frame

	}


	SDL_Quit();

	return 0;
}