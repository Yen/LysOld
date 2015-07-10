#pragma once

#include "vector4.hpp"

namespace lys
{

	class Matrix4
	{
	public:
		union
		{
			float elements[16];
			Vector4 blocks[4];
		};
	public:
		Matrix4();
		Matrix4(const float &diagonal);

		Matrix4 &multiply(const Matrix4 &other);
		friend Matrix4 operator *(Matrix4 left, const Matrix4 &right);
		Matrix4 &operator *=(const Matrix4 &other);

		Vector3 multiply(const Vector3 &other) const;
		friend Vector3 operator *(const Matrix4 &left, const Vector3 &right);

		Vector4 multiply(const Vector4 &other) const;
		friend Vector4 operator *(const Matrix4 &left, const Vector4 &right);

		Matrix4 &invert();

		bool operator ==(const Matrix4 &other) const;
		bool operator !=(const Matrix4 &other) const;
	};

}