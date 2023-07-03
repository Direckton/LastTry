#include "FileLoader.h"

struct block
{
	int x, y;
};

Fileloader::Fileloader()
{
	json data;
	std::ifstream fs("res/json/LEVEL1.json");
	if (fs.is_open())
	{
		data = json::parse(fs);

	}
	int value =0;
	try
	{
		value = data["level"]["blocks"]["block"]["y"].get<int>();

	}
	catch (json::type_error &t)
	{
		//std::cerr << "error" << std::endl;

	}

	for (auto it = data["blocks"].begin(); it != data["blocks"].end(); it++)
	{
		std::cout << it.value();

	}
}