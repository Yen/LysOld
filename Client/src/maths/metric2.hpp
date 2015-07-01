#pragma once

namespace lys
{

	class Metric2
	{
	public:
		int x;
		int y;
	public:
		Metric2();
		Metric2(const int &x, const int &y);

		bool operator ==(const Metric2 &other) const;
		bool operator !=(const Metric2 &other) const;
	};

}