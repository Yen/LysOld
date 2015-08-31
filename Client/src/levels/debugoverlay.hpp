#pragma once

#include "..\logic\level.hpp"

namespace lys
{

	class DebugOverlay : public Level
	{
	public:
		void draw(EngineCore &core, const FixedTimerData &time) override;
	};

}