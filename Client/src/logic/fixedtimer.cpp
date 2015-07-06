#include "fixedtimer.hpp"

namespace lys
{

	FixedTimer::FixedTimer()
	{
		reset();
	}

	void FixedTimer::reset()
	{
		using namespace std::chrono;

		_data.current = 0.0;
		_data.previous = 0.0;
		_data.delta = 0.0;

		_start = steady_clock::now();
	}

	void FixedTimer::update()
	{
		using namespace std::chrono;

		_data.previous = _data.current;
		_data.current = duration_cast<nanoseconds>(steady_clock::now() - _start).count() / 1000000000.0;
		_data.delta = _data.current - _data.previous;
	}

	const FixedTimerData &FixedTimer::getTimerData()
	{
		return _data;
	}

}