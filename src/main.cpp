#include "array_factory.h"

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <list>
#include <forward_list>
#include <deque>

int main()
{
	using FileArr = kg::FileArrays<std::vector, int>;
	using Factory = kg::ArrayFactory<std::vector, int>;
	using container = std::vector<int>;

	try
	{
		FileArr test("data/input.txt");

		/* Print */
		std::cout << "-------------\n";
		std::cout << "Printer:\n";
		std::cout << "-------------\n";
		auto printer = Factory::create(kg::Transformation::PRINT);
		printer->transform(test);

		std::cout << std::endl;

		/* Sort */
		std::cout << "-------------\n";
		std::cout << "Sorter:\n";
		std::cout << "-------------\n";
		auto sorter = Factory::create(kg::Transformation::SORT);
		sorter->transform(test);
		printer->transform(test);

		std::cout << std::endl;

		/* Intersection 2 */
		std::cout << "-------------\n";
		std::cout << "Intersection of 2:\n";
		std::cout << "-------------\n";
		auto inter2 = Factory::create(kg::Transformation::INTERSECT_2);
		auto cInter2 = std::static_pointer_cast<container>(inter2->transform(test));

		for (const auto i : *cInter2)
		{
			std::cout << i << " ";
		}

		std::cout << std::endl;

		/* Intersection All */
		std::cout << "-------------\n";
		std::cout << "Intersection of All:\n";
		std::cout << "-------------\n";
		auto inter = Factory::create(kg::Transformation::INTERSECT_ALL);
		auto cInter = std::static_pointer_cast<container>(inter->transform(test));

		for (const auto i : *cInter)
		{
			std::cout << i << " ";
		}

		std::cout << std::endl;

		/* Reversed sorted unique array */
		std::cout << "-------------\n";
		std::cout << "Reversed Sorted Unique Array:\n";
		std::cout << "-------------\n";
		auto revSet = Factory::create(kg::Transformation::UNIQUE_SORT_R);
		auto cRevSet = std::static_pointer_cast<container>(revSet->transform(test));

		for (const auto i : *cRevSet)
		{
			std::cout << i << " ";
		}
	}
	catch(const std::exception& err)
	{
		std::cout << "Error: " << err.what();
	}

	return 0;
}
