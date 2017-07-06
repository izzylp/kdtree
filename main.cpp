/* Compile and run: g++ -std=c++11 -W -Wall -O3 -o main main.cpp && ./main
 */

#include <iostream>
#include <cstdint>

#include "kdtree.hpp"

void print(point p)
{
	std::cout << p.to_string() << " ";
}

int main()
{
	{
		kdtree kdt({{10, 10}, {11, 13}, {9, 9}, {7, 12}, 
			   {8, 11}, {13, 5}, {12, 10}, {7, 8}, {13, 11}});
		std::cout << kdt.find({0, 0}) << std::endl;
		std::cout << kdt.find({10, 10}) << std::endl;
		std::cout << kdt.find({13, 11}) << std::endl;
		kdt.in_order(print);
		kdt.clear();
	}
	{
		kdtree kdt({{10, 10}, {11, 13}, {9, 9}, {7, 12}, 
			   {8, 11}, {13, 5}, {12, 10}, {7, 8}, {13, 11}});
		rect r(10, 13, 10, 13);
		std::vector<point> p_search = kdt.search(r);
		for (auto it = p_search.begin(); it != p_search.end(); ++it) {
			std::cout << it->to_string() << std::endl;
		}
		std::cout << "\n\n";
	}
	{
		kdtree kdt({{12, 10}, {11, 13}, {7, 8}, {7, 12}, 
			   {13, 15}, {8, 11}, {10, 10}, {9, 9}, {13, 11}});
		rect r(10, 13, 10, 13);
		std::vector<point> p_search = kdt.search(r);
		for (auto it = p_search.begin(); it != p_search.end(); ++it) {
			std::cout << it->to_string() << std::endl;
		}
		std::cout << "\n\n";
	}
	{
		kdtree kdt({{12, 10}, {12, 10}, {11, 13}, {7, 8}, {7, 12}, 
			   {13, 15}, {8, 11}, {10, 10}, {9, 9}, {13, 11}});
		rect r(10, 13, 10, 13);
		std::vector<point> p_search = kdt.search(r);
		for (auto it = p_search.begin(); it != p_search.end(); ++it) {
			std::cout << it->to_string() << std::endl;
		}
		std::cout << "\n\n";
	}
	{
		kdtree kdt({{1, 0}, {0, 1}, {2, 4}, {5, 7}, {8, 9}, 
			   {13, 151}, {4, 123}, {10, 10}, {9, 9}, {20, 11}});
		rect r(0, 5, 0, 5);
		std::vector<point> p_search = kdt.search(r);
		for (auto it = p_search.begin(); it != p_search.end(); ++it) {
			std::cout << it->to_string() << std::endl;
		}
		std::cout << "\n\n";
	}

	return 0;
}
