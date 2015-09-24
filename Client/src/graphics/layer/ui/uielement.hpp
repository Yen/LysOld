#pragma once

#include "..\..\..\maths.hpp"

namespace lys
{

	//TODO: implement UIElement
	class UIElement
	{
	public:
		enum Alignment : char
		{
			TOP_LEFT,
			TOP,
			TOP_RIGHT,
			RIGHT,
			BOTTOM_RIGHT,
			BOTTOM,
			BOTTOM_LEFT,
			LEFT,
			CENTER,
		};
	public:
		Metric2 size;
		Alignment alignment;
		Metric2 offset;
	};

}