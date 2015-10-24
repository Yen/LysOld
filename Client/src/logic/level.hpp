#pragma once

#include "fixedtimer.hpp"

namespace lys
{

#define LYS_LEVEL_DEFAULT_UPS 0

	class EngineLoadingArgs;
	class EngineInternals;
	class EngineArgs;

	class Level
	{
	public:
		const unsigned int _ups;
	public:
		Level(EngineInternals &internals, const EngineLoadingArgs &args, const int &ups = LYS_LEVEL_DEFAULT_UPS);
		virtual ~Level() = default;

		const unsigned int &getUPS() const;

		virtual void update(EngineInternals &internals, EngineArgs &args);
		virtual void draw(EngineInternals &internals, EngineArgs &args) = 0;

		virtual void resize(EngineInternals &internals);
	};

}