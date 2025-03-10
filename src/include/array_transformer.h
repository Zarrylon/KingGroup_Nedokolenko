#pragma once

/*
	Transform classes for Factory
*/

#include "file_arrays.h"
#include "array_utils.h"

#include <algorithm>

namespace kg
{
	template<template<typename...> typename TSubContainer, typename Type>
	class ArrayTransformer
	{
	public:
		virtual ~ArrayTransformer() = default;
		virtual std::shared_ptr<void> transform(kg::FileArrays<TSubContainer, Type>&) = 0;
	};

	template<template<typename...> typename TSubContainer, typename Type>
	class ArrayPrint : public ArrayTransformer<TSubContainer, Type>
	{
	public:
		virtual std::shared_ptr<void> transform(kg::FileArrays<TSubContainer, Type>& container) override
		{
			for (size_t i = 0; i < container.GetSubArrayCount(); i++)
			{
				kg::Print(container.SubBegin(i), container.SubEnd(i));
			}

			return nullptr;
		}
	};

	template<template<typename...> typename TSubContainer, typename Type, typename Compare = std::less<>>
	class ArraySort : public ArrayTransformer<TSubContainer, Type>
	{
	public:
		virtual std::shared_ptr<void> transform(kg::FileArrays<TSubContainer, Type>& container) override
		{
			for (size_t i = 0; i < container.GetSubArrayCount(); i++)
			{
				kg::Sort(container.GetSubArray(i));
			}

			return nullptr;
		}
	};

	template<template<typename...> typename TSubContainer, typename Type>
	class ArrayIntersect : public ArrayTransformer<TSubContainer, Type>
	{
	private:
		/* Members */
		bool doAll;

		/* Methods */
		std::pair<int, int> GetLongestArrIndexes(kg::FileArrays<TSubContainer, Type>& container)
		{
			/* <arrIndex, arrSize> */
			std::vector<std::pair<int, int>> tmp;

			for (size_t i = 0; i < container.GetSubArrayCount(); i++)
				kg::Insert(tmp, std::make_pair(i, container.GetSubArraySize(i)));

			auto comp = [](std::pair<int, int> a,
				std::pair<int, int> b) { return a.second > b.second; };

			std::sort(tmp.begin(), tmp.end(), comp);

			return std::make_pair(tmp[0].first, tmp[1].first);
		}

	public:
		ArrayIntersect(bool doForAll) : doAll(doForAll) {};

		virtual std::shared_ptr<void> transform(kg::FileArrays<TSubContainer, Type>& container) override
		{
			TSubContainer<Type> result;

			if (doAll)
			{
				result = container.GetSubArray(0);

				for (size_t i = 1; i < container.GetSubArrayCount(); i++)
				{
					result = kg::Intersection(result, container.GetSubArray(i));
				}
			}
			else
			{
				auto longestArrs = GetLongestArrIndexes(container);

				result = kg::Intersection(
					container.GetSubArray(longestArrs.first),
					container.GetSubArray(longestArrs.second)
				);
			}

			return std::make_shared<TSubContainer<Type>>(result);
		}
	};

	template<template<typename...> typename TSubContainer, typename Type>
	class ArrayToReversedSet : public ArrayTransformer<TSubContainer, Type>
	{
	private:
		void CountElements(std::map<Type, int, std::greater<Type>>& elements, const TSubContainer<Type>& container)
		{
			/* <element, count */
			for (const auto i : container)
			{
				elements[i]++;
			}
		}

	public:
		virtual std::shared_ptr<void> transform(kg::FileArrays<TSubContainer, Type>& container) override
		{
			std::map<Type, int, std::greater<Type>> elements;

			for (size_t i = 0; i < container.GetSubArrayCount(); i++)
			{
				CountElements(elements, container.GetSubArray(i));
			}

			TSubContainer<Type> result;

			for (const auto i : elements)
			{
				if (i.second == 1)
					Insert(result, i.first);
			}

			return std::make_shared<TSubContainer<Type>>(result);
		}
	};
}
