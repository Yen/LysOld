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

		bool operator ==(const Vector3 &other) const;
		bool operator !=(const Vector3 &other) const;
	};

}