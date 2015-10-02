#include <algorithm>
#include <random>


namespace Marox
{
	namespace Tools
	{
		namespace Random
		{
			template<typename T>
			void randomizeCollection(T& _collection)
			{
				std::random_device rd;
				std::mt19937 g(rd());
				std::shuffle(std::begin(_collection), std::end(_collection), g);
			}
			template<typename Iterator>
			void randomizeCollection(Iterator first, Iterator last)
			{
				std::random_device rd;
				std::mt19937 g(rd());
				std::shuffle(first, last, g);
			}


			double rand(double range_from, double range_to)
			{
				std::random_device rd;
				std::mt19937 mt(rd());
				//std::uniform_real_distribution<double> dist(range_from, range_to);
				std::uniform_real_distribution<double> dist(range_from, std::nextafter(range_to, DBL_MAX));
				return dist(mt);
			}
			int rand(int range_from, int range_to)
			{
				std::random_device rd;
				std::mt19937 mt(rd());
				//std::uniform_real_distribution<double> dist(range_from, range_to);
				//std::uniform_real_distribution<double> dist(range_from, std::nextafter(range_to, DBL_MAX));
				std::uniform_int_distribution<int> dist(range_from, range_to);
				return dist(mt);
			}
		}
	}
}