#include "FileLoader.h"

struct block
{
	int x, y;
};

Fileloader::Fileloader()
{
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

std::vector<std::pair<int, int>> Fileloader::specialElementCoordinates(json& data, std::string key)
{
	std::vector<std::pair<int, int>> output;
	try
	{
		//just iterate throug that and put it into vector or something
		auto coordinates = data[key].get<json::array_t>();
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

int Fileloader::getFinish(json& data)
{
	int finish = 0;
	try
	{
		finish = data["finish"];
	}
	catch (json::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return finish;
}

float Fileloader::getVolume(json& data, std::string var)
{
	float volume = 50;
	try
	{
		volume = data[var];
	}
	catch (json::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return volume;
}

void Fileloader::setVolume(json& data, std::string var, int volume)
{
	try
	{
		data[var] = volume;
	}
	catch (json::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

}

std::string Fileloader::getMusicTitle(json& data)
{
	std::string title = "";
	try
	{
		title = data["music"];
	}
	catch (json::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return title;
}