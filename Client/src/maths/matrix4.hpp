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
		static Matrix4 invert(const Matrix4 &matrix);

		Matrix4 &transpose();
		static Matrix4 transpose(const Matrix4 &matrix);

		static Matrix4 orthographic(float left, float right, float bottom, float top, float near, float far);
		static Matrix4 perspectivefov(float fov, float aspect, float near, float far);
		static Matrix4 perspectiveoffcenter(float left, float right, float bottom, float top, float near, float far);

		static Matrix4 lookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up);

		static Matrix4 translation(const Vector3 &translation);
		static Matrix4 rotation(float angle, const Vector3 &axis);
		static Matrix4 scale(const Vector3 &scale);

		bool operator ==(const Matrix4 &other) const;
		bool operator !=(const Matrix4 &other) const;
	};

}