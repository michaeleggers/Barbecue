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
			Uint32 width, 
			Uint32 height,
			Uint32 start_x,
			Uint32 start_y,
			Uint8 frames);
		~Sprite();

		// expose functions for now
		SDL_Texture* getTexture_();
		SDL_Rect getFrame_(Uint8);
		Uint8 frameCnt_();

	private:
		SpriteSheet* spriteSheet_;
		std::vector<SDL_Rect> frameRegions_;
		uint8_t frames_;
	};

}