#include "FileLoader.h"

Fileloader::Fileloader()
{
	json data;
	std::ifstream fs("res/json/test.json");
	if (fs.is_open())
	{
		data = json::parse(fs);

	}
	std::string value = data.value("x", "");

	std::cout << value << std::endl;
}