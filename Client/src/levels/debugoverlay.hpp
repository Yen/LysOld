#pragma once

#include "..\logic\level.hpp"

namespace lys
{

	class DebugOverlay : public Level
	{
	public:
		DebugOverlay(const EngineLoadingArgs &args);

		void draw(EngineInternals &internals, EngineArgs &args) override;
	};

}