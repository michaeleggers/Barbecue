#include "../inc/Map.h"
#include "fstream"
#include "../inc/rapidjson/document.h"
#include "../inc/rapidjson/writer.h"
#include "../inc/rapidjson/stringbuffer.h"

void Map::Load(const std::string path)
{
	using namespace rapidjson;
	std::ifstream t(path);
	std::string json((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	Document d;
	d.Parse(json.c_str());


}
