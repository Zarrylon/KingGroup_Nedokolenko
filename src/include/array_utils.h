#pragma once

/*
	Implementation of template container functions
	* Insert
	* Print
	* Sort
	* Intersection
*/

#include "type_handler.h"

#include <iostream>
#include <utility>
#include <map>

namespace kg
{
#pragma region Insert

	/* sequence containers */
	template <typename TSubContainer, typename Value>
	auto Insert(TSubContainer& container, Value&& value)
		-> decltype(container.push_back(std::forward<Value>(value)), void())
	{
		container.push_back(std::forward<Value>(value));
	}

	/* forward_list */
	template <typename TSubContainer, typename Value>
	auto Insert(TSubContainer& container, Value&& value)
		-> decltype(container.insert_after(container.before_begin(), std::forward<Value>(value)), void())
	{
		if (container.empty())
		{
			container.insert_after(container.before_begin(), std::forward<Value>(value));
		}
		else
		{
			auto it = container.before_begin();
			while (std::next(it) != container.end())
			{
				++it;
			}
			container.insert_after(it, std::forward<Value>(value));
		}
	}

	/* set */
	template <typename TSubContainer, typename Value>
	auto Insert(TSubContainer& container, Value&& value)
		-> decltype(container.insert(std::forward<Value>(value)), void())
	{
		container.insert(std::forward<Value>(value));
	}

#pragma endregion

#pragma region Print

	template <typename Iterator>
	typename std::enable_if<!is_pair<typename std::iterator_traits<Iterator>::value_type>::value>::type
		Print(Iterator begin, Iterator end)
	{
		for (auto i = begin; i != end; ++i)
		{
			std::cout << *i << " ";
		}
		std::cout << std::endl;
	}

	/* pair containers */
	template <typename Iterator>
	typename std::enable_if<is_pair<typename std::iterator_traits<Iterator>::value_type>::value>::type
		Print(Iterator begin, Iterator end)
	{
		for (auto i = begin; i != end; ++i)
		{
			std::cout << i->first << " ";
		}
		std::cout << std::endl;
	}

#pragma endregion

#pragma region Sort

	template<typename Iterator>
	void IteratorSwap(Iterator& a, Iterator& b)
	{
		auto tmp = *a;
		*a = *b;
		*b = tmp;
	}

	/* Quick Sort */
	template<typename Iterator, typename Compare = std::less<>>
	void QSort(const Iterator begin, const Iterator end, Compare comp = Compare())
	{
		if (std::distance(begin, end) > 1)
		{
			auto last = std::prev(end);
			auto pivot = *last;

			auto i = begin;
			auto j = i;

			while (j != last)
			{
				if (comp(*j, pivot))
				{
					IteratorSwap(i, j);
					++i;
				}

				++j;
			}

			IteratorSwap(i, last);

			QSort(begin, i, comp);
			QSort(std::next(i), end, comp);
		}
	}

	template<typename TSubContainer, typename Compare = std::less<>>
	typename std::enable_if<!is_associative_container<TSubContainer>::value, void>::type
		Sort(TSubContainer& container, Compare comp = Compare())
	{
		QSort(container.begin(), container.end(), comp);
	}

	template<typename Container, typename Compare = std::less<>>
	typename std::enable_if<is_associative_container<Container>::value, void>::type
		Sort(Container& container, Compare comp = Compare())
	{}


#pragma endregion

#pragma region Intersection

	template<template<typename...> typename TSubContainer, typename Type>
	typename std::enable_if<!is_map<TSubContainer<Type>>::value, TSubContainer<Type>>::type
		Intersection(TSubContainer<Type>& a, TSubContainer<Type>& b)
	{
		std::unordered_set<Type> sA(a.begin(), a.end());
		TSubContainer<Type> result;

		for (auto i = b.begin(); i != b.end(); ++i)
		{
			if (sA.find(*i) != sA.end())
			{
				kg::Insert(result, *i);
				sA.erase(*i);
			}
		}

		return result;
	}

#pragma endregion
}
