#include <algorithm>
#include <random>
#include <chrono>

namespace Marox
{
namespace Tools
	class Random final
	{
	public:
		Random() = delete;

		/// <summary>
		/// Randomizes a collection or an array
		/// </summary>
		/// <param name="_collection">Collection (having <c>begin()</c> and <c>end()</c>) or array</param>
		template<typename T>
		static void randomizeCollection(T& _collection)
		{
			//std::random_device rd;
			std::mt19937 g(randomDevice());
			std::shuffle(std::begin(_collection), std::end(_collection), g);
		}
		/// <summary>
		/// Randomizes a collection or an array
		/// </summary>
		/// <param name="first">iterator begin</param>
		/// <param name="last">iterator end</param>
		template<typename Iterator>
		static void randomizeCollection(Iterator first, Iterator last)
		{
			//std::random_device rd;
			std::mt19937 g(randomDevice());
			std::shuffle(first, last, g);
		}

		static double rand(double range_from, double range_to)
		{
			//std::random_device rd;
			std::mt19937 mt(randomDevice());
			//std::uniform_real_distribution<double> dist(range_from, range_to);
			std::uniform_real_distribution<double> dist(range_from, std::nextafter(range_to, DBL_MAX));
			return dist(mt);
		}
		static int rand(int range_from, int range_to)
		{
			//std::random_device rd;
			std::mt19937 mt(randomDevice());
			//std::uniform_real_distribution<double> dist(range_from, range_to);
			//std::uniform_real_distribution<double> dist(range_from, std::nextafter(range_to, DBL_MAX));
			std::uniform_int_distribution<int> dist(range_from, range_to);
			return dist(mt);
		}

	private:
		static std::random_device randomDevice;
	}
}
}
