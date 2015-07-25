#pragma once

#include "metric2.hpp"

namespace lys
{

	class Vector3;

	class Metric3
	{
	public:
		union
		{
			struct
			{
				int x;
				int y;
			};
			Metric2 xy;
		};
		int z;
	public:
		Metric3();
		Metric3(const Metric2 &xy, const int &z);
		Metric3(const int &x, const int &y, const int &z);

		bool operator ==(const Metric3 &other) const;
		bool operator !=(const Metric3 &other) const;

		operator Vector3() const;
	};

}