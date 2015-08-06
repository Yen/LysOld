#pragma once

#include <queue>
#include "fixedtimer.hpp"

namespace lys
{

	class FPSCounter
	{
	private:
		std::queue<TimePoint> _times;
	public:
		void push(const TimePoint &time);
		size_t getFPS(const TimePoint &current);
	};

}