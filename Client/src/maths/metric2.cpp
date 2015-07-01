#include "metric2.hpp"

namespace lys
{

	Metric2::Metric2()
		: x(0), y(0)
	{}

	Metric2::Metric2(int x, int y)
		: x(x), y(y)
	{}

	bool Metric2::operator ==(const Metric2 &other) const
	{
		return((x == other.x) && (y == other.y));
	}

	bool Metric2::operator !=(const Metric2 &other) const
	{
		return !(*this == other);
	}

}