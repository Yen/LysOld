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
		Texture _tex;
		Sprite _test;
		Label _label;
	public:
		Menu();

		void update(EngineCore &core, const FixedTimerData &time) override;
		void draw(EngineCore &core, const FixedTimerData &time) override;

		void resize(EngineCore &core) override;
	};

}