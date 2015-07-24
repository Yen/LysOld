#include "vector3.hpp"

#include <math.h>

#include "matrix4.hpp"

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

	Vector3 &Vector3::add(const Vector3 &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	Vector3 operator +(Vector3 left, const Vector3 &right)
	{
		return left.add(right);
	}

	Vector3 &Vector3::operator +=(const Vector3 &other)
	{
		return add(other);
	}

	Vector3 &Vector3::subtract(const Vector3 &other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	Vector3 operator -(Vector3 left, const Vector3 &right)
	{
		return left.subtract(right);
	}

	Vector3 &Vector3::operator -=(const Vector3 &other)
	{
		return subtract(other);
	}

	Vector3 &Vector3::multiply(const Vector3 &other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	Vector3 operator *(Vector3 left, const Vector3 &right)
	{
		return left.multiply(right);
	}

	Vector3 &Vector3::operator *=(const Vector3 &other)
	{
		return multiply(other);
	}

	Vector3 &Vector3::divide(const Vector3 &other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	Vector3 operator /(Vector3 left, const Vector3 &right)
	{
		return left.divide(right);
	}

	Vector3 &Vector3::operator /=(const Vector3 &other)
	{
		return divide(other);
	}

	Vector3 &Vector3::normalize()
	{
		float scale = 1.0f / length();
		x *= scale;
		y *= scale;
		z *= scale;

		return *this;
	}

	Vector3 Vector3::normalize(const Vector3 &vector)
	{
		Vector3 result = vector;
		return result.normalize();
	}

	Vector3 &Vector3::cross(const Vector3 &other)
	{
		Vector3 result;

		result.x = y * other.z - z * other.y;
		result.y = z * other.x - x * other.z;
		result.z = x * other.y - y * other.x;

		*this = result;

		return *this;
	}

	Vector3 Vector3::cross(const Vector3 &left, const Vector3 &right)
	{
		Vector3 result = left;
		return result.cross(right);
	}

	float Vector3::dot(const Vector3 &other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	float Vector3::dot(const Vector3 &left, const Vector3 &right)
	{
		return left.dot(right);
	}

	Vector3 &Vector3::transform(const Matrix4 &other)
	{
		Vector3 result;
		result.x = Vector3::dot(*this, Vector3(other.blocks[0].x, other.blocks[1].x, other.blocks[2].x)) + other.blocks[3].x;
		result.y = Vector3::dot(*this, Vector3(other.blocks[0].y, other.blocks[1].y, other.blocks[2].y)) + other.blocks[3].y;
		result.z = Vector3::dot(*this, Vector3(other.blocks[0].z, other.blocks[1].z, other.blocks[2].z)) + other.blocks[3].z;
		*this = result;
		return *this;
	}

	Vector3 Vector3::transform(const Vector3 &left, const Matrix4 &right)
	{
		Vector3 result = left;
		return result.transform(right);
	}

	bool Vector3::operator ==(const Vector3 &other) const
	{
		return((x == other.x) && (y == other.y) && (x == other.z));
	}

	bool Vector3::operator !=(const Vector3 &other) const
	{
		return !(*this == other);
	}

	float Vector3::length()
	{
		return sqrtf(x * x + y * y + z * z);
	}

}