#pragma once

#include "..\..\..\maths.hpp"

namespace lys
{

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
		Vector2 size;
		Alignment alignment;
		Vector2 offset;
	};

}