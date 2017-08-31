#include <iostream>

#include "../inc/Sprite.h"

bbq::Sprite::Sprite(
	SpriteSheet* spriteSheet, 
	Uint32 width,
	Uint32 height,
	Uint32 start_x,
	Uint32 start_y,
	Uint8 frames)
{
	spriteSheet_ = spriteSheet;
	frames_ = frames;

	Uint32 maxFramesPerRow = spriteSheet_->width_ / width;
	Uint32 maxFramesPerCol = spriteSheet_->height_ / height;

	std::cout << maxFramesPerRow << " " << maxFramesPerCol << std::endl;


	for (int index = 0; index < frames_; ++index)
	{
		SDL_Rect frame = 
		{ 
			(start_x + index * width) % spriteSheet_->width_, // top left x
			(((width * index) / spriteSheet_->width_) * height) + start_y,	   // top left y
			width,								   // x + width
			height								   // y + height
		};
		frameRegions_.push_back(frame);
		std::cout << "frame " << index << ", x: " << frame.x << ", y: " << frame.y << std::endl;
	}
}

bbq::Sprite::~Sprite()
{
}

SDL_Texture * bbq::Sprite::getTexture_()
{
	return spriteSheet_->texture_;
}

SDL_Rect bbq::Sprite::getFrame_(Uint8 index)
{
	return frameRegions_.at(index);
}

Uint8 bbq::Sprite::frameCnt_()
{
	return frames_;
}

