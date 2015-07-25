#pragma once

#include "..\window.hpp"
#include "fixedtimer.hpp"

namespace lys
{

#define LYS_LEVEL_DEFAULT_UPS 0

	class Level
	{
	public:
		const unsigned int _ups;
	public:
		Level();
		Level(const int &ups);
		virtual ~Level();

		const unsigned int &getUPS() const;

		virtual void update(Window &window, const FixedTimerData &time);
		virtual void draw(Window &window, const FixedTimerData &time) = 0;

		virtual void resize(Window &window);
	};

}