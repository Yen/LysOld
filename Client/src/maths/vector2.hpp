#pragma once

namespace lys
{

	class Metric2;

	class Vector2
	{
	public:
		float x;
		float y;
	public:
		Vector2();
		Vector2(const float &x, const float &y);

		Vector2 &add(const Vector2 &other);
		friend Vector2 operator +(Vector2 left, const Vector2 &right);
		Vector2 &operator +=(const Vector2 &other);

		Vector2 &subtract(const Vector2 &other);
		friend Vector2 operator -(Vector2 left, const Vector2 &right);
		Vector2 &operator -=(const Vector2 &other);

		Vector2 &multiply(const Vector2 &other);
		friend Vector2 operator *(Vector2 left, const Vector2 &right);
		Vector2 &operator *=(const Vector2 &other);

		Vector2 &divide(const Vector2 &other);
		friend Vector2 operator /(Vector2 left, const Vector2 &right);
		Vector2 &operator /=(const Vector2 &other);

		bool operator ==(const Vector2 &other) const;
		bool operator !=(const Vector2 &other) const;

		operator Metric2() const;
	};

}