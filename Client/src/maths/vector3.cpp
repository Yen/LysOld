#include "vector3.hpp"

namespace lys
{

	Vector3::Vector3()
		: x(0.0f), y(0.0f), z(0.0f)
	{}

	Vector3::Vector3(const Vector2 &xy, const float &z)
		: xy(xy), z(z)
	{}

	Vector3::Vector3(const float &x, const float &y, const float &z)
		: x(x), y(y), z(z)
	{}

	bool Vector3::operator ==(const Vector3 &other) const
	{
		return((x == other.x) && (y == other.y) && (x == other.z));
	}

	bool Vector3::operator !=(const Vector3 &other) const
	{
		return !(*this == other);
	}

}