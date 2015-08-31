#pragma once

#include "fixedtimer.hpp"

namespace lys
{

#define LYS_LEVEL_DEFAULT_UPS 0

	class EngineCore;

	class Level
	{
	public:
		const unsigned int _ups;
	public:
		Level();
		Level(const int &ups);
		virtual ~Level();

		const unsigned int &getUPS() const;

		virtual void update(EngineCore &core, const FixedTimerData &time);
		virtual void draw(EngineCore &core, const FixedTimerData &time) = 0;

		virtual void resize(EngineCore &core);
	};

}