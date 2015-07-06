#pragma once

#include <chrono>

namespace lys
{

	typedef double TimePoint;

	class FixedTimerData
	{
	public:
		TimePoint current;
		TimePoint previous;
		TimePoint delta;
	};

	class FixedTimer
	{
	private:
		FixedTimerData _data;
		std::chrono::time_point<std::chrono::steady_clock> _start;
	public:
		FixedTimer();

		void reset();
		void update();
		const FixedTimerData &getTimerData();
	};

}