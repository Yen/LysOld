#include "metric2.hpp"

#include "vector2.hpp"

namespace lys
{

	Metric2::Metric2()
		: x(0), y(0)
	{}

	Metric2::Metric2(const int &x, const int &y)
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

	Metric2::operator Vector2() const
	{
		return Vector2((float)x, (float)y);
	}

}