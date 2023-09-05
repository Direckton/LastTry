#pragma once
#include <json.hpp>
#include <fstream>
#include <iostream>
#include <tuple>

using namespace nlohmann;

class Fileloader
{
private:
	//json json;
public:
	Fileloader();
	~Fileloader() {}

	json getJson(std::string name);
	std::vector<std::pair<int, int>> getBlockCoordinates(json& data);
	std::vector<std::pair<int, int>> getSpikeCoordinates(json& data);
	int * getColor(json& data);
	int getFinish(json& data);


	int getHighscore(const json &data);

	json setHighscore(json data, const int score);

	void saveToFile(json& data, std::string path);

	float getVolume(json& data, std::string var);

	std::string getMusicTitle(json& data);

	
};
