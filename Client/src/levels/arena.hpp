#pragma once

#include "..\logic\level.hpp"
#include "..\graphics\layer\ui\uilayer.hpp"
#include "..\graphics\framebuffer.hpp"

namespace lys
{

	class Arena : public Level
	{
	private:
		UILayer _ui;
		UIElement _test[2];
		FrameBuffer _fb;
	public:
		Arena(EngineInternals &internals, const EngineLoadingArgs &args);

		void draw(EngineInternals &internals, EngineArgs &args) override;

		void resize(EngineInternals &internals) override;
	};

}