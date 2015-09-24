#include "fpscounter.hpp"

namespace lys
{

	void FPSCounter::push(const TimePoint &time)
	{
		_times.push(time);
	}

	const FPSInfo &FPSCounter::getFPS(const TimePoint &current)
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
		_info.fps = _times.size();
		_info.delay = 1000.0f / (float)_info.fps;
		return _info;
	}

}