#include "../inc/Map.h"
#include "../inc/Tile.h"
#include "fstream"
#include "../inc/rapidjson/document.h"
#include "../inc/rapidjson/writer.h"
#include "../inc/rapidjson/stringbuffer.h"
#include <sstream>


namespace bbq
{
	void Map::Load(const std::string path)
	{
		using namespace rapidjson;
		std::ifstream t(path);

		std::stringstream buffer;
		buffer << t.rdbuf();
		std::string json = buffer.str();

		Document d;
		d.Parse(json.c_str());

		Value& w = d["width"];
		Value& h = d["height"];

		width = w.GetInt();
		height = h.GetInt();

		map = (TileType*)malloc(width*height * sizeof(TileType));

		Value& layers = d["layers"];
		auto layers_list = layers.GetArray();

		Value& layer = layers_list[0];
		Value& layer_data = layer["data"];

		auto map_actual_data = layer_data.GetArray();

		for (int i = 0; i < map_actual_data.Size(); ++i)
		{
			Value& map_tile = map_actual_data[i];
			int id = map_tile.GetInt();
			TileType type = TileType::Free;

			if (id == 0)
			{
				type = TileType::Free;
			}
			else if (id == 1)
			{
				type = TileType::Free;
			}
			else if (id == 2)
			{
				type = TileType::Free;
			}
			else if (id == 3)
			{
				type = TileType::Box1;
			}
			else if (id == 4)
			{
				type = TileType::Wall;
			}
      else if (id == 6)
      {
        type = TileType::Box2;
      }
			*(map + i) = type;
		}
	}
}
