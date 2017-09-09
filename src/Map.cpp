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

		map = (Tile*)malloc(width*height * sizeof(Tile));

		Value& layers = d["layers"];
		auto layers_list = layers.GetArray();

		Value& layer = layers_list[0];
		Value& layer_data = layer["data"];

		auto map_actual_data = layer_data.GetArray();

		for (int i = 0; i < map_actual_data.Size(); ++i)
		{
			Value& map_tile = map_actual_data[i];
			int id = map_tile.GetInt();

			Tile* tile = new (map + i) Tile(TileType::Free, i % width, i / width, nullptr, this);
		}
	}
}
