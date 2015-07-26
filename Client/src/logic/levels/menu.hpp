#pragma once

#include "..\level.hpp"
#include "..\..\graphics\interfacebatch.hpp"
#include "..\..\graphics\sprite.hpp"
#include "..\..\graphics\sprites\label.hpp"

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

		void update(Window &window, const FixedTimerData &time) override;
		void draw(Window &window, const FixedTimerData &time) override;

		void resize(Window &window) override;
	};

}