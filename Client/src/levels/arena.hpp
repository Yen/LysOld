#pragma once

#include <vector>

#include "..\logic\level.hpp"
#include "..\graphics\layer\ui\uilayer.hpp"
#include "..\graphics\framebuffer.hpp"
#include "..\graphics\layer\ui\elements\simpleimageelement.hpp"

namespace lys
{

	class Arena : public Level
	{
	private:
		UILayer _ui;
		SimpleImageElement _test1;
		SimpleImageElement _test2;
		SimpleImageElement _test3;
		SimpleImageElement _test4;
		FrameBuffer _fb;
	public:
		Arena(EngineInternals &internals, const EngineLoadingArgs &args);

		void draw(EngineInternals &internals, EngineArgs &args) override;

		void resize(EngineInternals &internals) override;
	};

}