#pragma once

#include "metric2.hpp"

namespace lys
{

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
		Metric3(Metric2 xy, int z);
		Metric3(int x, int y, int z);

		bool operator ==(const Metric3 &other) const;
		bool operator !=(const Metric3 &other) const;
	};

}