#pragma once

#include <queue>
#include "fixedtimer.hpp"

namespace lys
{

	struct FPSInfo
	{
	public:
		size_t fps;
		float delay;
	};

	class FPSCounter
	{
	private:
		std::queue<TimePoint> _times;
		FPSInfo _info;
	public:
		void push(const TimePoint &time);
		const FPSInfo &getFPS(const TimePoint &current);
	};

}