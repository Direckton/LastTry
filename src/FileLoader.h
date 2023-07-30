#pragma once
#include <json.hpp>
#include <fstream>
#include <iostream>

using namespace nlohmann;

class Fileloader
{
private:
	//json json;
public:
	Fileloader();
	~Fileloader() {}

	json getJson(std::string name);
	std::vector<std::pair<int, int>> getCoordinates(json& data);

};
