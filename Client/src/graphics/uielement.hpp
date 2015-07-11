#pragma once

#include "..\window.hpp"
#include "..\logic\fixedtimer.hpp"

namespace lys
{

	class UIElement
	{
	public:
		virtual void draw(Window *window, const FixedTimerData &time) = 0;
	};

}