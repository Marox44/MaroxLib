#include <chrono>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <random>
#include <Windows.h>

namespace Marox
{
	namespace Tools
	{
		namespace Window
		{
			/// <summary>
			/// Hides the console window.
			/// </summary>
			void hideConsoleWindow()
			{
				ShowWindow(GetConsoleWindow(), SW_HIDE);
			}
			/// <summary>
			/// Shows the console window.
			/// </summary>
			void showConsoleWindow()
			{
				ShowWindow(GetConsoleWindow(), SW_SHOW);
			}
		}
		/// <summary>
		/// Returns current time and date
		/// </summary>
		/// <returns>Returns <c>string</c> in the following format: <c>YYYY-MM-DD HH:MM:SS</c></returns>
		std::string return_current_time_and_date()
		{
			auto now = std::chrono::system_clock::now();
			auto in_time_t = std::chrono::system_clock::to_time_t(now);

			std::stringstream ss;
			ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
			return ss.str();
		}
		/// <summary>
		/// Randomizes a collection or an array
		/// </summary>
		/// <param name="_collection">Collection (having <c>begin()</c> and <c>end()</c>) or an array</param>
		template<typename T>
		void randomizeCollection(T& _collection)
		{
			std::random_device rd;
			std::mt19937 g(rd());
			std::shuffle(std::begin(_collection), std::end(_collection), g);
		}
	}
}