#pragma once

namespace lys
{

	class Vector2
	{
	public:
		float x;
		float y;
	public:
		Vector2();
		Vector2(const float &x, const float &y);

		bool operator ==(const Vector2 &other) const;
		bool operator !=(const Vector2 &other) const;
	};

}