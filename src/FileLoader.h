#pragma once
#include <json.hpp>
#include <fstream>
#include <iostream>
#include <tuple>

using namespace nlohmann;

/**Class responsible for file manipulation*/
class Fileloader
{
public:
	Fileloader();
	~Fileloader() {}
	/**Returns json data from specified file path*/
	json getJson(std::string path);
	/**Retrieves coordinates of blockas and returns vector*/
	std::vector<std::pair<int, int>> getBlockCoordinates(json& data);
	/**Retrieves coordinates of spikes and returns vector*/
	std::vector<std::pair<int, int>> getSpikeCoordinates(json& data);
	/**Retrieves coordinates of boosters and double jumps and returns vector*/
	std::vector<std::pair<int, int>> specialElementCoordinates(json& data, std::string key);
	/**Gets color informaction in RGB format and returns array*/
	int * getColor(json& data);
	/**Gets finish position in GRID units*/
	int getFinish(json& data);
	/**Gets previous highscore*/
	int getHighscore(const json &data);
	/**Overrides given higscore in a json data*/
	json setHighscore(json data, const int score);
	/**Saves json data into json file*/
	void saveToFile(json& data, std::string path);
	/**Returns volume of given key in var*/
	float getVolume(json& data, std::string var);
	/**Sets volume of given key in var*/
	void setVolume(json& data, std::string var, int volume);
	/**Returns music title to play in specific level. 
	The title is saved in json*/
	std::string getMusicTitle(json& data);

	
};
