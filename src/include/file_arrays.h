#pragma once

/*
	* File parser to templated input containers
	* Stores them in std::array
*/

#include "file_handler.h"
#include "array_utils.h"

#include <exception>
#include <array>
#include <unordered_set>

namespace kg
{
	template<template<typename...> typename TSubContainer, typename Type>
	class FileArrays
	{
	private:
		/* Members */
		static const size_t ArrayCount = 3;
		const std::unordered_set<char> delimiters = { ',', ' ' };
		std::array<TSubContainer<Type>, ArrayCount> inputArrs;

		/* Methods */
		void CheckIndex(size_t index) const
		{
			if (index >= inputArrs.size())
				throw std::out_of_range("Index out of range");
		}

		/* string -> int */
		template<typename T = Type>
		typename std::enable_if<std::is_integral<T>::value, T>::type
			ConvertString(const std::string& str)
		{
			return std::stoi(str);
		}

		/* string -> float */
		template<typename T = Type>
		typename std::enable_if<std::is_floating_point<T>::value, T>::type
			ConvertString(const std::string& str)
		{
			return std::stof(str);
		}

		/* string -> string */
		template<typename T = Type>
		typename std::enable_if<std::is_same<T, std::string>::value, T>::type
			ConvertString(const std::string& str)
		{
			return str;
		}

		void ParseNumber(const std::string& line, const int arrIndex)
		{
			std::string number;

			for (const auto ch : line)
			{
				if (std::isdigit(ch)
					|| (ch == '-' && number.empty()))
				{
					number += ch;
				}
				else if (delimiters.find(ch) != delimiters.end())
				{
					if (!number.empty())
					{
						if (number.size() == 1 && number[0] == '-')
							throw std::exception("Expected number after \'-\'.");

						kg::Insert(inputArrs[arrIndex], ConvertString(number));
						number.clear();
					}
				}
				else throw std::exception("Unexpected delimiter.");
			}

			if (!number.empty())
				kg::Insert(inputArrs[arrIndex], ConvertString(number));
		}

		void ParseToArray(kg::FileHandler& file)
		{
			for (int i = 0; i < GetSubArrayCount(); i++)
			{
				std::string line = file.ReadLine();
				ParseNumber(line, i);
			}
		}

	public:
		/* Constructors */
		FileArrays(kg::FileHandler& file)
		{
			ParseToArray(file);
		}

		FileArrays(const std::string& fileName)
		{
			kg::FileHandler file(fileName);
			ParseToArray(file);
		}

		~FileArrays() = default;
		FileArrays(const FileArrays&) = default;
		FileArrays(FileArrays&&) noexcept = default;

		FileArrays& operator=(const FileArrays&) = default;
		FileArrays& operator=(FileArrays&&) noexcept = default;

		/* Iterators */
		auto Begin()
		{
			return inputArrs.begin();
		}

		auto End()
		{
			return inputArrs.end();
		}

		auto SubBegin(size_t index)
		{
			CheckIndex(index);
			return inputArrs[index].begin();
		}

		auto SubEnd(size_t index)
		{
			CheckIndex(index);
			return inputArrs[index].end();
		}

		/* Misc */
		std::array<TSubContainer<Type>, ArrayCount>& GetArray()
		{
			return inputArrs;
		}

		const std::array<TSubContainer<Type>, ArrayCount>& GetArray() const
		{
			return inputArrs;
		}

		TSubContainer<Type>& GetSubArray(size_t index)
		{
			CheckIndex(index);
			return inputArrs[index];
		}

		const TSubContainer<Type>& GetSubArray(size_t index) const
		{
			CheckIndex(index);
			return inputArrs[index];
		}

		size_t GetSubArrayCount() const
		{
			return ArrayCount;
		}

		size_t GetSubArraySize(size_t index) const
		{
			auto tmp = GetSubArray(index);
			return std::distance(tmp.begin(), tmp.end());
		}
	};
}
