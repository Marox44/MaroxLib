#pragma once
#include <chrono>

namespace Marox
{
	/// <summary>
	/// Miscl tools  //todo
	/// </summary>
	namespace Tools
	{
		/// <summary>
		/// Use Timers to indicate 'points' between which you want to measure time
		/// </summary>
		/// <example> Example usage:
		/// <code>
		/// Marox::Tools::Timer t1;
		/// actions_to_be_done();
		/// Marox::Tools::Timer t2;
		/// auto duration = Marox::Tools::Timer::getDuration_milliseconds(t1,t2);
		/// </code>
		/// </example>
		class Timer final
		{
		public:
			/// <summary>
			/// Creates a <c>Timer</c>
			/// </summary>
			Timer()
			{
				this->T = std::chrono::high_resolution_clock::now();
			}
			~Timer() = default;
			/// <summary>
			/// Get time elapsed between two <c><see cref="Timer"/>s</c>
			/// </summary>
			/// <param name="timer_begin">Initial <c>Timer</c></param>
			/// <param name="timer_end">Ending <c>Timer</c></param>
			/// <returns>Duration in <c>milliseconds</c></returns>
			static double getDuration_milliseconds(const Timer& timer_begin, const Timer& timer_end)
			{
				auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timer_end.T - timer_begin.T).count();
				return duration;
			}
			/// <summary>
			/// Get time elapsed between two <c><see cref="Timer"/>s</c>
			/// </summary>
			/// <param name="timer_begin">Initial <c>Timer</c></param>
			/// <param name="timer_end">Ending <c>Timer</c></param>
			/// <returns>Duration in <c>seconds</c></returns>
			static double getDuration_seconds(const Timer& timer_begin, const Timer& timer_end)
			{
				auto duration = std::chrono::duration_cast<std::chrono::seconds>(timer_end.T - timer_begin.T).count();
				return duration;
			}
		private:
			std::chrono::high_resolution_clock::time_point T;
		};
	}
}