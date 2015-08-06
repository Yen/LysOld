#include "fpscounter.hpp"

namespace lys
{

	void FPSCounter::push(const TimePoint &time)
	{
		_times.push(time);
	}

	size_t FPSCounter::getFPS(const TimePoint &current)
	{
		while (!_times.empty())
		{
			if (_times.front() < current - 1)
			{
				_times.pop();
				continue;
			}
			break;
		}
		return _times.size();
	}

}