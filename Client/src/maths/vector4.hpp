#pragma once

#include "vector3.hpp"

namespace lys
{

	class Matrix4;

	class Vector4
	{
	public:
		union
		{
			struct
			{
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
			};
			Vector3 xyz;
		};
		float w;
	public:
		Vector4();
		Vector4(const Vector2 &xy, const float &z, const float &w);
		Vector4(const Vector3 &xyz, const float &w);
		Vector4(const float &x, const float &y, const float &z, const float &w);

		Vector4 &transform(const Matrix4 &matrix);
		static Vector4 transform(const Vector4 &left, const Matrix4 &right);

		bool operator ==(const Vector4 &other) const;
		bool operator !=(const Vector4 &other) const;
	};

}