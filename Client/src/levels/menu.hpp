#pragma once

#include "..\logic\level.hpp"
#include "..\graphics\layer\ui\uilayer.hpp"
#include "..\graphics\layer\ui\elements\uilabel.hpp"
#include "..\graphics\layer\ui\elements\uitexture.hpp"
#include "..\graphics\layer\layerrenderer.hpp"

namespace lys
{

	class Menu : public Level
	{
	private:
		LayerRenderer _renderer;
		UILayer _ui;
		UILabel _label;
		UITexture _button;
		Metric2 _previousMouse;
	public:
		Menu(EngineInternals &internals, const EngineLoadingArgs &args);

		void update(EngineInternals &internals, EngineArgs &args) override;
		void draw(EngineInternals &internals, EngineArgs &args) override;

		void resize(EngineInternals &internals) override;
	};

}