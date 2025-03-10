/*
	RAII file opener/closer
*/

#include "file_handler.h"

kg::FileHandler::FileHandler(const std::string& fileName) : fileName(fileName)
{
	inputFile.open(this->fileName);

	if (!inputFile)
		throw std::runtime_error("Can't open the " + fileName);
}

kg::FileHandler::~FileHandler()
{
	if (inputFile.is_open())
		inputFile.close();
}

std::string kg::FileHandler::ReadLine()
{
	std::string line;
	std::getline(inputFile, line, '\n');

	return line;
}
