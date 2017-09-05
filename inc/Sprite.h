#pragma once

#include <vector>

#include "SpriteSheet.h"

/*
	Takes reference to SpriteSheet and
	renders only the portion (eg Walkcycle) it needs.
*/

namespace bbq
{
	class Sprite
	{
	public:
		Sprite(
			SpriteSheet* spriteSheet,
			int width, 
			int height,
			Uint32 start_x,
			Uint32 start_y,
			Uint8 frames);
		~Sprite();

		// expose functions for now
		SDL_Texture* getTexture_();
		SDL_Rect getFrame_(Uint8);
		Uint8 frameCnt_();
    int setPos(Uint32 x, Uint32 y);
    int& getPosX();
    int& getPosY();
    int setScale(Uint32 x, Uint32 y);
    SDL_Rect getPosAndScale();

	private:
		SpriteSheet* spriteSheet_;
		std::vector<SDL_Rect> frameRegions_;
		uint8_t frames_;
    SDL_Rect posAndScale_;
	};

}