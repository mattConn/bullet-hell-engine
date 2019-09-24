#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "global.h"
#include "gameObj.h"

void bulletsFromFile(std::string fileName, std::map<std::string, gameObj> &objMap)
{
	std::ifstream infile(fileName);

	std::string line;
	std::string tok;

	std::vector<std::string> args;

	while(std::getline(infile, line))
	{
		if(line[0] != '#') // check for line comment
		{
			std::stringstream ss(line); // stringstream from line

			while(std::getline(ss, tok, ' ')) // space delimiter
				args.push_back(tok);

			global::allTextures[args[1]] = global::loadTexture(args[1].c_str());
			objMap[args[0]] = gameObj(args[1], std::stoi(args[2]), std::stoi(args[3]), std::stoi(args[4]));
		}

		line = "";
		tok = "";
		args.clear();
	}

	infile.close();
}

void enemiesFromFile(std::string fileName, std::map<std::string, gameObj> &objMap)
{
	std::ifstream infile(fileName);

	std::string line;
	std::string tok;

	std::vector<std::string> args;

	while(std::getline(infile, line))
	{
		if(line[0] != '#') // check for line comment
		{
			std::stringstream ss(line); // stringstream from line

			while(std::getline(ss, tok, ' ')) // space delimiter
				args.push_back(tok);

			global::allTextures[args[1]] = global::loadTexture(args[1].c_str());

			objMap[args[0]] = gameObj(args[1], std::stoi(args[2]), std::stoi(args[3]), std::stoi(args[4]), 0, 0, args[5], std::stoi(args[6]));


		}

		line = "";
		tok = "";
		args.clear();
	}

	infile.close();

}
