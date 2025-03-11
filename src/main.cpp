/* Works with the following containers:
* ----------------------- *
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <unordered_set>
* ----------------------- *
*/

#include "array_factory.h"

#include <iostream>
#include <vector>

int main()
{
	using FileArr = kg::FileArrays<std::vector, int>;
	using Factory = kg::ArrayFactory<std::vector, int>;
	using Container = std::vector<int>;

	try
	{
		FileArr test("data/input.txt");

		/* Print */
		std::cout << "----------------------------------------\n";
		std::cout << "Printer:\n";
		auto printer = Factory::create(kg::Transformation::PRINT);
		printer->transform(test);
		//std::cout << "----------------------------------------\n";


		/* Sort */
		std::cout << "----------------------------------------\n";
		std::cout << "Sorter:\n";
		auto sorter = Factory::create(kg::Transformation::SORT);
		sorter->transform(test);
		printer->transform(test);

		/* Intersection 2 */
		std::cout << "----------------------------------------\n";
		std::cout << "Intersection of 2 longest:\n";
		auto inter2 = Factory::create(kg::Transformation::INTERSECT_2);
		auto cInter2 = std::static_pointer_cast<Container>(inter2->transform(test));

		for (const auto i : *cInter2)
		{
			std::cout << i << " ";
		}

		/* Intersection All */
		std::cout << "\n----------------------------------------\n";
		std::cout << "Intersection of All:\n";
		auto inter = Factory::create(kg::Transformation::INTERSECT_ALL);
		auto cInter = std::static_pointer_cast<Container>(inter->transform(test));

		for (const auto i : *cInter)
		{
			std::cout << i << " ";
		}

		/* Reversed sorted unique array */
		std::cout << "\n----------------------------------------\n";
		std::cout << "Reversed Sorted Unique Array:\n";
		auto revSet = Factory::create(kg::Transformation::UNIQUE_SORT_R);
		auto cRevSet = std::static_pointer_cast<Container>(revSet->transform(test));

		for (const auto i : *cRevSet)
		{
			std::cout << i << " ";
		}
	}
	catch(const std::exception& err)
	{
		std::cout << "Error: " << err.what();
	}

	std::cout << "\n----------------------------------------\n";

	return 0;
}
