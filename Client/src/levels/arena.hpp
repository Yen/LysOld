#pragma once

#include "..\logic\level.hpp"

namespace lys
{

	class Arena : public Level
	{
	public:
		Arena(EngineInternals &internals, const EngineLoadingArgs &args);

		void draw(EngineInternals &internals, EngineArgs &args) override;
	};

}