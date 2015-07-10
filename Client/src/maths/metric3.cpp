#include "metric3.hpp"

namespace lys
{

	Metric3::Metric3()
		: x(0), y(0), z(0)
	{}

	Metric3::Metric3(const Metric2 &xy, const int &z)
		: xy(xy), z(z)
	{}

	Metric3::Metric3(const int &x, const int &y, const int &z)
		: x(x), y(y), z(z)
	{}

	bool Metric3::operator ==(const Metric3 &other) const
	{
		return((x == other.x) && (y == other.y) && (x == other.z));
	}

	bool Metric3::operator !=(const Metric3 &other) const
	{
		return !(*this == other);
	}

}