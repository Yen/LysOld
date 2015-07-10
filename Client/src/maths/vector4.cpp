#include "vector4.hpp"

namespace lys
{

	Vector4::Vector4()
		: x(0), y(0), z(0), w(0)
	{}

	Vector4::Vector4(const Vector2 &xy, const float &z, const float &w)
		: xy(xy), z(z), w(w)
	{}

	Vector4::Vector4(const Vector3 &xyz, const float &w)
		: xyz(xyz), w(w)
	{}

	Vector4::Vector4(const float &x, const float &y, const float &z, const float &w)
		: x(x), y(y), z(z), w(w)
	{}

	bool Vector4::operator ==(const Vector4 &other) const
	{
		return((x == other.x) && (y == other.y) && (x == other.z) && (x == other.w));
	}

	bool Vector4::operator !=(const Vector4 &other) const
	{
		return !(*this == other);
	}

}