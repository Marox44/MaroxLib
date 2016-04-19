#pragma once

#include <iostream>
#include <Windows.h>
#include <iomanip>

namespace Marox
{
	namespace WinAPI
	{
		namespace Console
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

			bool progressBar(double d)
			{
				int max = 50;
				std::cout << std::fixed << std::setprecision(2) << d << "% ";
				std::cout << " [";
				int steps = (int)((d / 100) * max);
				for (int i = 0; i < steps; i++)
				{
					std::cout << "=";
				}
				std::cout << ">" << "\r";
				if (steps == max)
				{
					//std::cout << std::endl;
				}

				return 0;
			}
		}
	}
}