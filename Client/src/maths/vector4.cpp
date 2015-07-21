#include "vector4.hpp"

#include "matrix4.hpp"

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

	Vector4 &Vector4::transform(const Matrix4 &matrix)
	{
		Vector4 result;
		result.x = x * matrix.blocks[0].x + y * matrix.blocks[1].x + z * matrix.blocks[2].x + w * matrix.blocks[3].x;
		result.y = x * matrix.blocks[0].y + y * matrix.blocks[1].y + z * matrix.blocks[2].y + w * matrix.blocks[3].y;
		result.z = x * matrix.blocks[0].z + y * matrix.blocks[1].z + z * matrix.blocks[2].z + w * matrix.blocks[3].z;
		result.w = x * matrix.blocks[0].w + y * matrix.blocks[1].w + z * matrix.blocks[2].w + w * matrix.blocks[3].w;
		*this = result;
		return *this;
	}

	Vector4 Vector4::transform(const Vector4 &left, const Matrix4 &right)
	{
		Vector4 result = left;
		return result.transform(right);
	}

	bool Vector4::operator ==(const Vector4 &other) const
	{
		return((x == other.x) && (y == other.y) && (x == other.z) && (x == other.w));
	}

	bool Vector4::operator !=(const Vector4 &other) const
	{
		return !(*this == other);
	}

}