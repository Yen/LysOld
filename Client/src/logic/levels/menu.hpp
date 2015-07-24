#pragma once

#include "..\level.hpp"
#include "..\..\graphics\interfacebatch.hpp"
#include "..\..\graphics\sprite.hpp"

namespace lys
{

	class Menu : public Level
	{
	private:
		InterfaceBatch _interface;
		Sprite _test;
	public:
		Menu();

		void update(Window &window, const FixedTimerData &time) override;
		void draw(Window &window, const FixedTimerData &time) override;

		void resize(Window &window) override;
	};

}