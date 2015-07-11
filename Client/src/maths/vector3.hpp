#pragma once

#include "vector2.hpp"

namespace lys
{

	class Vector3
	{
	public:
		union
		{
			struct
			{
				float x;
				float y;
			};
			Vector2 xy;
		};
		float z;
	public:
		Vector3();
		Vector3(const Vector2 &xy, const float &z);
		Vector3(const float &x, const float &y, const float &z);

		Vector3 &add(const Vector3 &other);
		friend Vector3 operator +(Vector3 left, const Vector3 &right);
		Vector3 &operator +=(const Vector3 &other);

		Vector3 &subtract(const Vector3 &other);
		friend Vector3 operator -(Vector3 left, const Vector3 &right);
		Vector3 &operator -=(const Vector3 &other);

		Vector3 &multiply(const Vector3 &other);
		friend Vector3 operator *(Vector3 left, const Vector3 &right);
		Vector3 &operator *=(const Vector3 &other);

		Vector3 &divide(const Vector3 &other);
		friend Vector3 operator /(Vector3 left, const Vector3 &right);
		Vector3 &operator /=(const Vector3 &other);

		Vector3 &normalize();
		static Vector3 normalize(const Vector3 &vector);

		Vector3 &cross(const Vector3 &other);
		static Vector3 cross(const Vector3 &left, const Vector3 &right);

		bool operator ==(const Vector3 &other) const;
		bool operator !=(const Vector3 &other) const;
	private:
		float length();
	};

}