#pragma once

/*
	Factory Pattern 
*/

#include "array_transformer.h"

namespace kg
{
	enum class Transformation : short
	{
		PRINT, SORT, INTERSECT_2, INTERSECT_ALL, UNIQUE_SORT_R
	};

	template<template<typename...> typename TSubContainer, typename Type>
	class ArrayFactory
	{
	public:
		static std::unique_ptr<ArrayTransformer<TSubContainer, Type>> create(const Transformation t)
		{
			switch (t)
			{
			case Transformation::PRINT:
				return std::make_unique<ArrayPrint<TSubContainer, Type>>();

			case Transformation::SORT:
				return std::make_unique<ArraySort<TSubContainer, Type>>();

			case Transformation::INTERSECT_2:
				return std::make_unique<ArrayIntersect<TSubContainer, Type>>(false);

			case Transformation::INTERSECT_ALL:
				return std::make_unique<ArrayIntersect<TSubContainer, Type>>(true);

			case Transformation::UNIQUE_SORT_R:
				return std::make_unique<ArrayToReversedSet<TSubContainer, Type>>();

			default:
				return nullptr;
			}
		}
	};
}
