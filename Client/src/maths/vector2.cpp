#include "vector2.hpp"

namespace lys
{

	Vector2::Vector2()
		: x(0.0f), y(0.0f)
	{}

	Vector2::Vector2(const float &x, const float &y)
		: x(x), y(y)
	{}

	bool Vector2::operator ==(const Vector2 &other) const
	{
		return((x == other.x) && (y == other.y));
	}

	bool Vector2::operator !=(const Vector2 &other) const
	{
		return !(*this == other);
	}

}