#pragma once

#include "..\logic\level.hpp"
#include "..\graphics\interfacebatch.hpp"
#include "..\graphics\sprite.hpp"
#include "..\graphics\sprites\label.hpp"

namespace lys
{

	class Menu : public Level
	{
	private:
		InterfaceBatch _interface;
		Texture2D _tex;
		Sprite _test;
		Label _label;
		Metric2 _previousMouse;
	public:
		Menu(EngineInternals &internals, const EngineLoadingArgs &args);

		void update(EngineInternals &internals, EngineArgs &args) override;
		void draw(EngineInternals &internals, EngineArgs &args) override;

		void resize(EngineInternals &internals) override;
	};

}