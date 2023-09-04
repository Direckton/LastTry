#include "FileLoader.h"

struct block
{
	int x, y;
};

Fileloader::Fileloader()
{
	json data;
	std::ifstream fs("res/json/level/LEVEL1.json");
	if (fs.is_open())
	{
		data = json::parse(fs);

	}
	std::string value;
	try
	{
		//just iterate throug that and put it into vector or something
		auto x = data["blocks"].get<json::array_t>();
		std::cout << x[1].at("x");
		std::cout << x[1].at("y");
	}
	catch (json::exception &e)
	{
		std::cout << e.what() << std::endl;

	}

	/*for (auto it = data["blocks"].begin(); it != data["blocks"].end(); it++)
	{
		std::cout << std::setw(2)<<  it.value();
		json iData = it.value();
		std::cout << iData["x"].get<int>();

	}*/
}

json Fileloader::getJson( std::string name)
{
	json data;
	std::ifstream fs(name);
	if (fs.is_open())
	{
		data = json::parse(fs);
	}
	fs.close();
	return data;
}

std::vector<std::pair<int, int>> Fileloader::getBlockCoordinates(json &data)
{
	std::vector<std::pair<int, int>> output;
	try
	{
		//just iterate throug that and put it into vector or something
		auto coordinates = data["blocks"].get<json::array_t>();
		for (int i = 0; i < coordinates.size(); i++)
		{
			int x = coordinates[i].at("x");
			int y = coordinates[i].at("y");
			output.push_back(std::pair<int, int>(x,y));
		}
	}
	catch (json::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return output;
}

std::vector<std::pair<int, int>> Fileloader::getSpikeCoordinates(json& data)
{
	std::vector<std::pair<int, int>> output;
	try
	{
		//just iterate throug that and put it into vector or something
		auto coordinates = data["spikes"].get<json::array_t>();
		for (int i = 0; i < coordinates.size(); i++)
		{
			int x = coordinates[i].at("x");
			int y = coordinates[i].at("y");
			output.push_back(std::pair<int, int>(x, y));
		}
	}
	catch (json::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return output;
}

int * Fileloader::getColor(json& data)
{
	int rgb[3];
	try
	{
		auto color = data["color"].get<json::array_t>();

		rgb[0]= color[0].at("r");
		rgb[1]= color[0].at("g");
		rgb[2]= color[0].at("b");

	}
	catch (json::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return rgb;
}

int Fileloader::getHighscore(const json &data)
{
	int result=0;
	try
	{
		result = data["highscore"];
	}
	catch (json::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return result;
}

json Fileloader::setHighscore(json data, const int score)
{
	try
	{
		data["highscore"] = score;
	}
	catch (json::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return data;
}

void Fileloader::saveToFile(json& data, std::string path)
{
	std::ofstream output(path);
	if (output.is_open());
	{
		output << data;
	}
	output.close();
}