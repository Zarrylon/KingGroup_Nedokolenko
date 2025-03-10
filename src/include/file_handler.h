#pragma once

/*
	RAII file opener/closer
*/

#include <fstream>
#include <string>

namespace kg
{
	class FileHandler
	{
	private:
		std::ifstream inputFile;
		std::string fileName;

	public:
		FileHandler(const std::string&);
		~FileHandler();

		std::string ReadLine();

		/* Deleted Copy & Move */
		FileHandler(const FileHandler&) = delete;
		FileHandler(FileHandler&&) = delete;
		FileHandler& operator=(const FileHandler&) = delete;
		FileHandler& operator=(FileHandler&&) = delete;
	};
}
