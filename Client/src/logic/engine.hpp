#pragma once

#include "..\window.hpp"
#include "fixedtimer.hpp"
#include "..\graphics\spritebatch.hpp"

namespace lys
{

	class Engine
	{
	private:
		Window *_window;
		FixedTimer *_timer;
		SpriteBatch *_spriteBatch;
	public:
		Engine();
		~Engine();

		void run();
	};

}