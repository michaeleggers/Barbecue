#pragma once
#include "TileInterface.h"
#include "../inc/Player.h"

#include <map>



namespace bbq
{
	extern std::map<TileType, Sprite*> type_to_sprite;
	extern std::map<TileType, int> type_to_sprite_idx;
  extern SDL_AudioDeviceID deviceId;

}